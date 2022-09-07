#pragma once

#include <SDL.h>
#include <array>
#include <string>

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

class GraphicalObject {
public:
    virtual void draw(SDL_Renderer*) = 0;
private:
};

class BackgroundImage: public GraphicalObject {
public:
    BackgroundImage();
    void draw(SDL_Renderer*) final;
private:
    void generate_random_stars();
    std::array<SDL_Point, STAR_COUNT> stars;
};

class Terrain: public GraphicalObject {
public:
    Terrain();
    void draw(SDL_Renderer*) final;
private:
    void generate_random_terrain();
    std::array<SDL_Point, HILLS_COUNT> hills;
};
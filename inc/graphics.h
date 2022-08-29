#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

namespace colors
{
    constexpr SDL_Color white {255,255,255};
    constexpr SDL_Color black {0,0,0};
}

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

class UI: public GraphicalObject {
public:
    UI();
    ~UI();
private:
    SDL_Texture* ui_texture;
    TTF_Font* ui_font;
    TTF_Font* title_font;
};

class Terrain: public GraphicalObject {
public:
    Terrain();
    ~Terrain();
    void draw(SDL_Renderer*) final;
private:
    void generate_random_terrain();
    std::array<SDL_Point, HILLS_COUNT> hills;
};
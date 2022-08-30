#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include <string>

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

enum font_type{
    TITLE_FONT,
    UI_FONT,
    FONT_NUM
};

namespace color
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
    UI(SDL_Renderer*);
    ~UI();
    void prepare_textures(std::string, font_type);
    void draw(SDL_Renderer*) final;
private:
    int width;
    int height;
    SDL_Renderer* renderer;
    SDL_Texture* ui_texture;
    std::array<TTF_Font*, FONT_NUM> fonts;
};

class Terrain: public GraphicalObject {
public:
    Terrain();
    void draw(SDL_Renderer*) final;
private:
    void generate_random_terrain();
    std::array<SDL_Point, HILLS_COUNT> hills;
};
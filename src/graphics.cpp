#include "graphics.h"
#include <random>
#include <algorithm>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

void BackgroundImage::generate_random_stars()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distwidth(1,SCREEN_WIDTH);
    std::uniform_int_distribution<std::mt19937::result_type> distheight(1,SCREEN_HEIGHT);
    for (int i=0; i<STAR_COUNT; ++i) {
        stars[i] = SDL_Point{int(distwidth(rng)), int(distheight(rng))};
    }
}

void BackgroundImage::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderDrawPoints(renderer,stars.data(),STAR_COUNT);
}

BackgroundImage::BackgroundImage()
{
    generate_random_stars();
}

UI::UI(SDL_Renderer* renderer_): renderer{renderer_}
{
    fonts[TITLE_FONT] = TTF_OpenFont("../oscilloscope.ttf",35);
    fonts[UI_FONT] = TTF_OpenFont("../oscilloscope.ttf",15);
}

UI::~UI()
{
    std::for_each(fonts.begin(), fonts.end(), TTF_CloseFont);
}

void UI::prepare_textures(std::string text, font_type font)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(fonts[font],text.c_str(),color::white);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
    }
    else {
        //Create texture from surface pixels
        ui_texture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if (ui_texture == NULL){
            printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
        }
    }
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void UI::draw(SDL_Renderer* renderer)
{
    SDL_Rect render_quad = {200,300,width,height};

    //Render to screen
    SDL_RenderCopy(renderer,ui_texture,NULL,&render_quad);
}

void Terrain::generate_random_terrain()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distheight(0,SCREEN_HEIGHT/10);
    int height = 0;
    for (int i=0; i<HILLS_COUNT; ++i) {
        height += int(distheight(rng)) - SCREEN_HEIGHT/20;
        if (height < 0) {
            height -= height;
        }
        hills[i] = SDL_Point{SCREEN_WIDTH/HILLS_COUNT*i,SCREEN_HEIGHT-height};
    }
}

void Terrain::draw(SDL_Renderer* renderer)
{
    SDL_RenderDrawLines(renderer,hills.data(),HILLS_COUNT);
}

Terrain::Terrain()
{
    generate_random_terrain();
}
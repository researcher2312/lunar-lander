#include "graphics.h"
#include <random>

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
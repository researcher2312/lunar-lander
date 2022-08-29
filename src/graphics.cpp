#include "graphics.h"
#include <random>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;
constexpr int STAR_COUNT = 50;

void BackgroundImage::generate_random_stars()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distwidth(1,SCREEN_WIDTH);
    std::uniform_int_distribution<std::mt19937::result_type> distheight(1,SCREEN_HEIGHT);
    for (int i=0; i<STAR_COUNT; ++i) {
        stars.emplace_back(Vector2D{int(distwidth(rng)), int(distheight(rng))});
    }
}

void BackgroundImage::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    for (auto coordinates: stars) {
        SDL_RenderDrawPoint(renderer, coordinates.x, coordinates.y);
    }
}

BackgroundImage::BackgroundImage()
{
    generate_random_stars();
}
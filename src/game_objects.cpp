#include <random>
#include "game_objects.h"
#include "game.h"

void GameObject::draw(SDL_Renderer& renderer)
{
    m_graphics->invoke_renderer(&renderer);
}

void BackgroundImage::generate_random_stars()
{
    std::vector<SDL_Point> points(STAR_COUNT);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distwidth(1,SCREEN_WIDTH);
    std::uniform_int_distribution<std::mt19937::result_type> distheight(1,SCREEN_HEIGHT);
    for (int i=0; i<STAR_COUNT; ++i) {
        points[i] = SDL_Point{int(distwidth(rng)), int(distheight(rng))};
    }
}

BackgroundImage::BackgroundImage()
{
    m_graphics = new GraphicalPoints(false);
    m_graphics->setColor(color::white);
    generate_random_stars();
}

BackgroundImage::~BackgroundImage()
{
    delete(m_graphics);
}

void Terrain::generate_random_terrain()
{
    std::vector<SDL_Point> points(HILLS_COUNT);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distheight(0,SCREEN_HEIGHT/10);
    int height = 0;
    for (int i=0; i<HILLS_COUNT; ++i) {
        height += int(distheight(rng)) - SCREEN_HEIGHT/20;
        if (height < 0) {
            height -= height;
        }
        points[i] = SDL_Point{SCREEN_WIDTH/HILLS_COUNT*i,SCREEN_HEIGHT-height};
    }
}

Terrain::Terrain()
{
    m_graphics = new GraphicalPoints(true);
    m_graphics->setColor(color::white);
    generate_random_terrain();
}

Lander::Lander()
{

}

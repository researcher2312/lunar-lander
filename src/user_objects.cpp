#include <random>
#include <iostream>
#include "game.h"
#include "user.objects.h"
#include "lander_points.h"

void BackgroundImage::generate_random_stars()
{
    std::vector<SDL_Point> points(STAR_COUNT);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distwidth(1,SCREEN_WIDTH);
    std::uniform_int_distribution<std::mt19937::result_type> distheight(1,SCREEN_HEIGHT);
    for (int i=0; i<STAR_COUNT; ++i) {
        points.at(i) = SDL_Point{int(distwidth(rng)), int(distheight(rng))};
    }
    stars->set_points(points);
}

BackgroundImage::BackgroundImage()
{
    stars = new GraphicalPoints(false);
    stars->set_color(color::white);
    generate_random_stars();
}

BackgroundImage::~BackgroundImage()
{
    delete(stars);
}

void BackgroundImage::draw(Renderer& renderer)
{
    stars->invoke_renderer(renderer);
}

void BackgroundImage::update(float)
{

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
    hills->set_points(points);
}
void Terrain::draw(Renderer& renderer)
{
    hills->invoke_renderer(renderer);
}

Terrain::Terrain()
{
    hills = new GraphicalPoints(true);
    hills->set_color(color::white);
    generate_random_terrain();
}

Terrain::~Terrain()
{
    delete(hills);
}

void Terrain::update(float)
{

}

Lander::Lander()
{
    chassis = new GraphicalPoints(true);
    chassis->set_color(color::white);
    chassis->set_points(test);
    physics = new RigidBody(1000);
}

Lander::~Lander()
{
    delete(chassis);
    delete(physics);
}

void Lander::draw(Renderer& renderer)
{
    chassis->invoke_renderer(renderer);
}

void Lander::update(float frame_time)
{
    physics->update(frame_time);
    chassis->set_position(physics->get_position());
    // std::cerr << physics->get_position().x << ' ' << physics->get_position().y << '\n';
}

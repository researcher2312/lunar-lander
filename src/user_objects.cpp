#include <random>
#include <iostream>
#include "utils.h"
#include "game.h"
#include "user_objects.h"
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
    chassis->set_points(lander_shape);

    flame = new GraphicalPoints(true);
    flame->set_color(color::white);
    flame->set_points(flame_shape);

    physics = new RigidBody(1000);
    physics->set_position({50, 0});
    engine_on = false;
    engine_flame_percent = 0;
}

Lander::~Lander()
{
    delete(chassis);
    delete(physics);
}

void Lander::draw(Renderer& renderer)
{
    chassis->invoke_renderer(renderer);
    flame->invoke_renderer(renderer);
}

void Lander::update(float frame_time)
{
    if(engine_on) {
        if (engine_flame_percent < 100) {
            ++engine_flame_percent;
        }
    }
    else if (engine_flame_percent > 0) {
        --engine_flame_percent;
    }
    if (engine_flame_percent > 0){
        physics->apply_force(rotate_point(SDL_FPoint{0, -20*engine_flame_percent/100}, physics->get_rotation()));
    }

    physics->update(frame_time);
    chassis->set_position(physics->get_position());
    chassis->set_rotation(physics->get_rotation());

    flame->stretch_points(1, engine_flame_percent/100);
    // std::cerr << physics->get_position().x << ' ' << physics->get_position().y << '\n';
}

void Lander::receive_key_press(SDL_Keycode key)
{
    switch(key) {
        case SDLK_UP:
        engine_on = true;
        break;

        case SDLK_LEFT:
        physics->set_rotation_speed(-0.02);
        break;

        case SDLK_RIGHT:
        physics->set_rotation_speed(0.02);
        break;
    }
}

void Lander::receive_key_release(SDL_Keycode key)
{
    switch(key) {
        case SDLK_UP:
        engine_on = false;
        break;

        case SDLK_LEFT:
        physics->set_rotation_speed(0);
        break;

        case SDLK_RIGHT:
        physics->set_rotation_speed(0);
        break;
    }
}

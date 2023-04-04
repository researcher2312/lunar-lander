#pragma once

#include "graphics.h"
#include "physics.h"

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

class GameObject {
public:
    void draw(SDL_Renderer&);
    SDL_Point get_position() const;
    void update();
protected:
    SDL_Point m_position;
    GraphicalObject* m_graphics = nullptr;
    PhysicalObject* m_physics = nullptr;
};

class BackgroundImage: public GameObject {
public:
    BackgroundImage();
    virtual ~BackgroundImage();
private:
    void generate_random_stars();
};

class Terrain: public GameObject {
public:
    Terrain();
    virtual ~Terrain();
private:
    void generate_random_terrain();
};

class Lander: public GameObject {
public:
    Lander();
    virtual ~Lander();
private:

};

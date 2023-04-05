#pragma once

#include "graphics.h"
#include "physics.h"

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

class GameObject {
public:
    virtual void draw(Renderer&)=0;
    SDL_Point get_position() const;
    void update();
protected:
    SDL_Point m_position;
};

class BackgroundImage: public GameObject {
public:
    BackgroundImage();
    virtual ~BackgroundImage();
    void draw(Renderer&) override;
private:
    GraphicalPoints* stars;
    void generate_random_stars();
};

class Terrain: public GameObject {
public:
    Terrain();
    virtual ~Terrain();
    void draw(Renderer&) override;
private:
    GraphicalPoints* hills;
    void generate_random_terrain();
};

class Lander: public GameObject {
public:
    Lander();
    virtual ~Lander();
    void draw(Renderer&) override;
private:
    GraphicalPoints* chassis;
};

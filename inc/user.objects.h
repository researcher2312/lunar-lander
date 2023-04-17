#pragma once

#include "graphics.h"
#include "physics.h"
#include "game_object.h"

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

class BackgroundImage: public GameObject {
public:
    BackgroundImage();
    virtual ~BackgroundImage();
    void draw(Renderer& renderer) override;
private:
    GraphicalPoints* stars;
    void generate_random_stars();
};

class Terrain: public GameObject {
public:
    Terrain();
    virtual ~Terrain();
    void draw(Renderer& renderer) override;
private:
    GraphicalPoints* hills;
    void generate_random_terrain();
};

class Lander: public GameObject {
public:
    Lander();
    virtual ~Lander();
    void draw(Renderer& renderer) override;
    void move();
private:
    GraphicalPoints* chassis;
    // PhysicalObject* physics;
};

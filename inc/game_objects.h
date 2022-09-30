#pragma once

#include "graphics.h"
#include "physics.h"

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

class BackgroundImage: public GraphicalPoints {
public:
    BackgroundImage();
private:
    void generate_random_stars();
};

class Terrain: public GraphicalLines {
public:
    Terrain();
private:
    void generate_random_terrain();
};



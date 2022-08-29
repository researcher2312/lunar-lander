#pragma once

#include <SDL.h>

class GraphicalObject {
public:
    virtual void draw(SDL_Renderer*) = 0;
private:
};

class BackgroundImage : GraphicalObject {
public:
    void draw(SDL_Renderer*) final;
private:
void generate_random_stars();
};
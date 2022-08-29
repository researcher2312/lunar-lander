#pragma once

#include <SDL.h>
#include <list>

struct Vector2D {
    int x;
    int y;
};

class GraphicalObject {
public:
    virtual void draw(SDL_Renderer*) = 0;
private:
};

class BackgroundImage: public GraphicalObject {
public:
    BackgroundImage();
    void draw(SDL_Renderer*) final;
private:
    void generate_random_stars();
    std::list<Vector2D> stars;
};

#pragma once

#include "graphics.h"
#include <SDL.h>
#include <memory>
#include <list>

class GameWindow {
public:
    GameWindow();
    ~GameWindow();
    void update_graphics();
    void add_new_graphical_object(GraphicalObject*);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::list<GraphicalObject*> graphical_objects;
};

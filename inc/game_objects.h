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
    void add_new_graphical_object();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::list<std::unique_ptr<GraphicalObject>> graphical_objects;
};
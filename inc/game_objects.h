#pragma once

#include <memory>
#include <list>
#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "ui.h"


class GameWindow {
public:
    GameWindow();
    ~GameWindow();
    void update_graphics();
    void add_new_graphical_object(GraphicalObject*);
    SDL_Renderer* get_renderer() {return renderer;};
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::list<GraphicalObject*> graphical_objects;
    UI ui;
};

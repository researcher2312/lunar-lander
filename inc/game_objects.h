#pragma once

#include <SDL.h>

class GameWindow {
public:
    GameWindow();
    ~GameWindow();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
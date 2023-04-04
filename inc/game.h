#pragma once

#include <memory>
#include <list>
#include <array>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ui.h"
#include "graphics.h"
#include "game_objects.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class GameWindow {
public:
    GameWindow();
    ~GameWindow();
    void update_graphics();
    void add_new_graphical_object(GameObject*);
    // SDL_Renderer* get_renderer() {return renderer;};
private:
    SDL_Window* window;
    std::list<GameObject*> m_graphical_objects;
    std::unique_ptr<Renderer> m_renderer;
};

class Game {
public:
    Game();
    ~Game();
    void start();
    void finish();
    void update();
    void get_user_input();
private:
    GameWindow window;
    UI ui;
    BackgroundImage background;
    Terrain terrain;
};

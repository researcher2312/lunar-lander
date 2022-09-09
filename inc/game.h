#pragma once

#include <memory>
#include <list>
#include <array>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game_objects.h"
#include "ui.h"
#include "graphics.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

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
    std::array<TTF_Font*, FONT_NUM> fonts;
    void set_drawing_color(const SDL_Color&);
    void render(GraphicalObject*);
    void render(GraphicalLines*);
    void render(GraphicalPoints*);
    void render(GraphicalText*);
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

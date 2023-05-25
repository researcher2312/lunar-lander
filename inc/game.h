#pragma once

#include <memory>
#include <list>
#include <array>
#include <map>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ui.h"
#include "graphics.h"
#include "physics.h"
#include "game_object.h"
#include "user.objects.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/**
 * @brief Class for managing graphical display and rendering.
 * 
 */
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

/*!
 * @brief Class handling the user input data and the connected functions.
 * 
 */
class InputHandler {
public:
    void subscribe_action(SDL_Keycode, SDL_EventType, SignalReceiver*);
    void delete_action(SDL_Keycode, SDL_EventType);
    void handle_game_input(const SDL_Event&);
private:
    std::unordered_map<SDL_Keycode, SignalReceiver*> assigned_actions_press;
    std::unordered_map<SDL_Keycode, SignalReceiver*> assigned_actions_lift;
};

/**
 * @brief Main class to manage the game components.
 * 
 * In th0 future this class will be changed to a representation of just one game
 * state, and the game will consist of multiple following states.
 */
class Game {
public:
    Game();
    ~Game();
    void start();
    void finish();
    void update();
private:
    InputHandler m_input_handler;
    Timer fps_timer;
    GameWindow window;
    Physics physics;
    UI ui;
    BackgroundImage background;
    Terrain terrain;
    Lander lander;
    unsigned int frame_number = 0;
};

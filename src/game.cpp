#include <iostream>
#include <memory>
#include <algorithm>
#include "game.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

GameWindow::GameWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        std::cerr<<"SDL could not initialize! SDL_Error: %s\n"<<SDL_GetError();
    }
    if (TTF_Init()<0) {
        std::cerr<<"SDL_ttf could not initialize! SDL_ttf Error: %s\n"<<TTF_GetError();
    }
    //Create window
    window = SDL_CreateWindow("Lunar Lander",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == NULL) {
    }
    else {
        m_renderer = std::make_unique<Renderer>(window);
        SDL_Surface* icon = SDL_LoadBMP("../resources/icon.bmp");
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }
    std::cerr<<"Finished init\n";
}

GameWindow::~GameWindow()
{
    m_renderer.reset();
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    std::cerr<<"GameWindow destroyed\n";
}

/*!
 * @brief Performs all redrawing
 * 
 */
void GameWindow::update_graphics()
{
    //Clear screen
    m_renderer->set_drawing_color(color::black);
    m_renderer->clear_screen();
    //draw all objects
    for (auto rendered_object: m_graphical_objects) {
        rendered_object->draw(*m_renderer);
    }
    //Update screen
    m_renderer->show_screen();
}

/*!
 * @brief Adds new graphical object to list of rendered objects
 * 
 * @param new_object 
 */
void GameWindow::add_new_graphical_object(GameObject* new_object)
{
    m_graphical_objects.push_back(new_object);
}

/*!
 * @brief Save a function to be performed when a certain key is pressed
 * or released.
 * 
 * @param key 
 * @param event 
 * @param function 
 */
void InputHandler::subscribe_action(SDL_Keycode key,
                                    SDL_EventType event,
                                    SignalReceiver* receiver)
{
    if (event == SDL_KEYDOWN) {
        assigned_actions_press.insert({key, receiver});
    }
    else if (event == SDL_KEYUP) {
        assigned_actions_lift.insert({key, receiver});
    }

}

/*!
 * @brief Delete a connection between a key press/lift and a function call
 * 
 * @param key 
 * @param event 
 */
void InputHandler::delete_action(SDL_Keycode key, SDL_EventType event)
{
    if (event == SDL_KEYDOWN) {
        assigned_actions_press.erase(key);
    }
    else if (event == SDL_KEYUP) {
        assigned_actions_lift.erase(key);
    }
}

/*!
 * @brief Check the list of key subscriptions and activate the chosen keys
 * 
 * @param event 
 */
void InputHandler::handle_game_input(const SDL_Event& event)
{
    SDL_Keycode pressed_key = event.key.keysym.sym;
    if (event.type == SDL_KEYDOWN) {
        if (assigned_actions_press.find(pressed_key) !=
            assigned_actions_press.end()) {
            assigned_actions_press.at(pressed_key)->receive_key_press(pressed_key);
        }
    }
    else if (event.type == SDL_KEYUP) {
        if (assigned_actions_lift.find(pressed_key) !=
            assigned_actions_lift.end()) {
            assigned_actions_lift.at(pressed_key)->receive_key_release(pressed_key);
        }
    }
}

Game::Game()
{
    window.add_new_graphical_object(&background);
    window.add_new_graphical_object(&terrain);
    window.add_new_graphical_object(&lander);
    window.add_new_graphical_object(&ui);
    physics.add_new_physical_object(&lander);

    m_input_handler.subscribe_action(SDLK_UP, SDL_KEYDOWN, &lander);
    m_input_handler.subscribe_action(SDLK_UP, SDL_KEYUP, &lander);

    // lander.set_position(SDL_Point{250, 0});
    // ui.set_position(SDL_Point{250, 0});

}

Game::~Game()
{
}

/*!
 * @brief launches the main game loop
 * 
 */
void Game::start()
{
    std::cerr << "Game started\n";
    bool quit = false;
    SDL_Event e;
    fps_timer.start();
    while(!quit) {
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0){
            //User requests quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            /*else if (e.type == SDL_KEYDOWN) {
                user_key_down(e.key.keysym.sym);
            }
            else if (e.type == SDL_KEYUP) {
                user_key_up(e.key.keysym.sym);
            }*/
            m_input_handler.handle_game_input(e);
        }
        update();
    }
}

/*!
 * @brief performs the update at the end of a frame
 * 
 * This function performs an update of physics, graphics and frame number
 */
void Game::update()
{
    frame_number += 1;
    physics.tick();
    window.update_graphics();
    // if (frame_number%1000 == 0) {
    //     std::cerr <<  frame_number / (fps_timer.get_ticks() / 1000.f) << '\n';
    // }
    // ui.draw_ui();
}

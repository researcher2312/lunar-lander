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

Game::Game()
{
    window.add_new_graphical_object(&background);
    window.add_new_graphical_object(&terrain);
    window.add_new_graphical_object(&lander);
    window.add_new_graphical_object(&ui);
    physics.add_new_physical_object(&lander);

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
    if (frame_number%1000 == 0) {
        std::cerr <<  frame_number / (fps_timer.get_ticks() / 1000.f) << '\n';
    }
    // ui.draw_ui();
}

#include <iostream>
#include <memory>
#include <algorithm>
#include "game.h"
#include "ui.h"

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
    std::cerr<<"GameWindow destroyed\n";
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void GameWindow::update_graphics()
{
    //Clear screen
    m_renderer->set_drawing_color(color::black);
    m_renderer->clear_screen();
    //draw all objects
    for (auto rendered_object: m_graphical_objects) {
        rendered_object->invoke_renderer(*m_renderer);
    }
    //Update screen
    m_renderer->show_screen();
}

void GameWindow::add_new_graphical_object(GraphicalObject* new_object)
{
    m_graphical_objects.push_back(new_object);
}

Game::Game()
{
    window.add_new_graphical_object(&background);
    window.add_new_graphical_object(&terrain);
    // auto title = new UITextElement();
    // title->set_text("Lunar Lander",TITLE_FONT);
    // ui.add_ui_element(title);
}

Game::~Game()
{
}

void Game::start()
{
    std::cerr << "Game started\n";
    bool quit = false;
    SDL_Event e;
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

void Game::update()
{
    window.update_graphics();
    // ui.draw_ui();
}
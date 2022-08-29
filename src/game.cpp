#include <stdio.h>
#include <memory>
#include "game.h"

Game::Game()
{
    window.add_new_graphical_object(new BackgroundImage);
    window.add_new_graphical_object(new Terrain);
}

Game::~Game()
{
}

void Game::start()
{
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
}
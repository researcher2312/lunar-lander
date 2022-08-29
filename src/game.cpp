#include <stdio.h>
#include "game.h"

Game::Game()
{

}

Game::~Game()
{
}

void Game::start(){
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
        window.update_graphics();
    }
}
#include <stdio.h>
#include "game.h"

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
    }
}

Game::~Game()
{
    SDL_Quit();
}

void Game::start(){
    SDL_Delay(10000);
}
#include "game_objects.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

GameWindow::GameWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
    }
    //Create window
    window = SDL_CreateWindow("Lunar Lander",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
    }
    else {
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
        }
        SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
        SDL_RenderClear(renderer);
    }
}

GameWindow::~GameWindow()
{
    printf("GameWindow destroyed\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameWindow::update_graphics()
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
    SDL_RenderClear(renderer);

    //draw all objects
    for (auto rendered_object: graphical_objects) {
        rendered_object->draw(renderer);
    }

    //Update screen
    SDL_RenderPresent(renderer);
}

void GameWindow::add_new_graphical_object(GraphicalObject* new_object)
{
    graphical_objects.push_back(new_object);
}
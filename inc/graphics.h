#pragma once

#include <string>
#include <SDL.h>
extern SDL_Window* gWindow;
    
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

SDL_Texture* loadTexture(std::string);

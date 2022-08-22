#pragma once

#include <string>
#include <SDL.h>
extern SDL_Window* gWindow;
    
//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The image we will load and show on the screen
extern SDL_Surface* gHelloWorld;
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(std::string&);

//Frees media and shuts down SDL
void close();
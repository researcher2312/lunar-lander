#pragma once

#include <string>
#include <SDL.h>
extern SDL_Window* gWindow;
    
//The surface contained by the window
extern SDL_Surface* gScreenSurface;
//The image we will load and show on the screen
extern SDL_Surface* gKeyPressSurfaces[];
extern SDL_Surface* gCurrentSurface;
//Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

SDL_Surface* loadSurface(std::string);

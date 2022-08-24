#include "graphics.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = nullptr;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        // Create window
        gWindow = SDL_CreateWindow("Lunar Lander", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

// Loads media
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../graphics/default.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
        success = false;
        printf("Failed to load default image!\n" );
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../graphics/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
        success = false;
        printf("Failed to load left image!\n" );
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../graphics/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
        success = false;
        printf("Failed to load right image!\n" );
    }

    return success;
}

SDL_Surface* loadSurface(std::string file_name)
{
    //Load splash image
    SDL_Surface* loadedSurface = SDL_LoadBMP(file_name.c_str());
    return loadedSurface;
}

// Frees media and shuts down SDL
void close()
{
    //Deallocate surface
    //SDL_FreeSurface(gHelloWorld);
    //gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

#include <SDL_image.h>
#include "graphics.h"

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Current displayed texture
SDL_Texture* gTexture = nullptr;

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
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
            success = false;
        }
        else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image could not initialize! SDL_image Error: %s\n",IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

// Loads media
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load PNG texture
    gTexture = loadTexture("../graphics/test.png");
    if (gTexture == NULL ) {
        printf("Failed to load texture image!\n");
        success = false;
    }

    return success;
}

//loads new texture from png file
SDL_Texture* loadTexture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = nullptr;

    newTexture = IMG_LoadTexture(gRenderer,path.c_str());
    if (newTexture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n",path.c_str(),SDL_GetError());
    }

    return newTexture;
}

// Frees media and shuts down SDL
void close()
{
    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

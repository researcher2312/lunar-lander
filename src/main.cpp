#include <stdio.h>
#include <SDL.h>
#include "graphics.h"


int main(int argc, char* args[])
{
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        //Load media
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        }
    }
	//While application is running
	while (!quit) {
	//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				//Select surfaces based on key press
				switch(e.key.keysym.sym) {
					case SDLK_LEFT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

					case SDLK_RIGHT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

					default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}
		//Apply the current image
        SDL_BlitSurface(gCurrentSurface,NULL,gScreenSurface,NULL);
        //Update the surface
        SDL_UpdateWindowSurface(gWindow);
	}
    //Free resources and close SDL
    close();

    return 0;
}

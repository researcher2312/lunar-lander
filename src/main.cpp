#include <stdio.h>
#include <SDL.h>
#include "graphics.h"


int main(int argc, char* args[])
{
	std::string file_name {"../test.bmp"};
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else{
        //Load media
        if(!loadMedia(file_name)) {
            printf("Failed to load media!\n");
        }
    }
	//While application is running
	while(!quit) {
	//Handle events on queue
		while(SDL_PollEvent(&e) != 0) {
			//User requests quit
			if(e.type == SDL_QUIT) {
				quit = true;
			}
		}
		//Apply the image
		SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL );
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
	}
    //Free resources and close SDL
    close();

    return 0;
}


#include "game.h"
#include <stdio.h>
#include <memory>

Game::Game()
{
    ui = new UI(window.get_renderer());
    ui->prepare_textures("Lunar Lander", TITLE_FONT);
    window.add_new_graphical_object(&background);
    window.add_new_graphical_object(&terrain);
    window.add_new_graphical_object(ui);
}

Game::~Game()
{
    delete ui;
}

void Game::start()
{
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
        update();
    }
}

void Game::update()
{
    window.update_graphics();
}
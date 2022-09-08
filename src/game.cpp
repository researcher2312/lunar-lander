#include <stdio.h>
#include <memory>
#include "game.h"
#include "ui.h"

Game::Game()
{
    window.add_new_graphical_object(&background);
    window.add_new_graphical_object(&terrain);
    ui.set_renderer(window.get_renderer());
    auto title = new UITextElement();
    // title->set_text("Lunar Lander",TITLE_FONT);
    // ui.add_ui_element(title);
}

Game::~Game()
{
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
    // ui.draw_ui();
}
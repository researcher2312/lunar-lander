#include <iostream>
#include <memory>
#include <algorithm>
#include "game.h"
#include "ui.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

GameWindow::GameWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        std::cerr<<"SDL could not initialize! SDL_Error: %s\n"<<SDL_GetError();
    }
    if (TTF_Init()<0) {
        std::cerr<<"SDL_ttf could not initialize! SDL_ttf Error: %s\n"<<TTF_GetError();
    }
    fonts[TITLE_FONT] = TTF_OpenFont("../resources/oscilloscope.ttf",35);
    fonts[UI_FONT] = TTF_OpenFont("../resources/oscilloscope.ttf",15);
    //Create window
    window = SDL_CreateWindow("Lunar Lander",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == NULL) {
    }
    else {
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
        }
        SDL_Surface* icon = SDL_LoadBMP("../resources/icon.bmp");
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
        set_drawing_color(color::black);
        SDL_RenderClear(renderer);
    }
    std::cerr<<"Finished init\n";
}

GameWindow::~GameWindow()
{
    std::cerr<<"GameWindow destroyed\n";
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    std::for_each(fonts.begin(), fonts.end(), TTF_CloseFont);
    TTF_Quit();
    SDL_Quit();
}

void GameWindow::update_graphics()
{
    //Clear screen
    set_drawing_color(color::black);
    SDL_RenderClear(renderer);
    //draw all objects
    for (auto rendered_object: graphical_objects) {
        render(rendered_object);
    }
    //Update screen
    SDL_RenderPresent(renderer);
}

void GameWindow::add_new_graphical_object(GraphicalObject* new_object)
{
    graphical_objects.push_back(new_object);
}

void GameWindow::set_drawing_color(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);

}

void GameWindow::render(GraphicalObject*)
{
    std::cerr << "GraphicalObject\n";
}


void GameWindow::render(GraphicalPoints* rendered)
{
    set_drawing_color(rendered->getColor());
    SDL_RenderDrawPoints(renderer,rendered->get_points(),0);
}


void GameWindow::render(GraphicalLines* rendered)
{
    set_drawing_color(rendered->getColor());
    SDL_RenderDrawLines(renderer,rendered->get_points(),0);
}

// void GameWindow::render(GraphicalText* rendered)
// {

//     //Render to screen
//     SDL_RenderCopy(renderer,ui_texture,NULL,&render_quad);
// }

Game::Game()
{
    window.add_new_graphical_object(&background);
    window.add_new_graphical_object(&terrain);
    // auto title = new UITextElement();
    // title->set_text("Lunar Lander",TITLE_FONT);
    // ui.add_ui_element(title);
}

Game::~Game()
{
}

void Game::start()
{
    std::cerr << "Game started\n";
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
#include <algorithm>
#include <iostream>
#include "graphics.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

void GraphicalPoints::invoke_renderer(Renderer& renderer)
{
    renderer.render_points(this);
}

void GraphicalLines::invoke_renderer(Renderer& renderer)
{
    renderer.render_line(this);
}

// void GraphicalText::invoke_renderer(Renderer& renderer)
// {
//     if (modified) {
//         // render_texture();
//     }
// }

void GraphicalText::set_text(std::string text_, font_type font_)
{
    text = text_;
    font = font_;
}

// void GraphicalText::render_texture(TTF_Font* font, SDL_Renderer* renderer)
// {
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font,text.c_str(),color::white);
//     if (textSurface == NULL) {
//         printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
//     }
//     else {
//         //Create texture from surface pixels
//         ui_texture = SDL_CreateTextureFromSurface(renderer,textSurface);
//         if (ui_texture == NULL){
//             printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
//         }
//     }
//     size.x = textSurface->w;
//     size.y = textSurface->h;
//     SDL_FreeSurface(textSurface);
// }


Renderer::Renderer(SDL_Window* window)
{
    fonts[TITLE_FONT] = TTF_OpenFont("../resources/oscilloscope.ttf",35);
    fonts[UI_FONT] = TTF_OpenFont("../resources/oscilloscope.ttf",15);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    set_drawing_color(color::white);
    SDL_RenderClear(renderer);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    std::for_each(fonts.begin(), fonts.end(), TTF_CloseFont);
}

void Renderer::set_drawing_color(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);

}

void Renderer::render_points(const GraphicalPoints* rendered)
{
    set_drawing_color(rendered->getColor());
    SDL_RenderDrawPoints(renderer,rendered->get_points(),rendered->get_size());
}


void Renderer::render_line(const GraphicalLines* rendered)
{
    set_drawing_color(rendered->getColor());
    SDL_RenderDrawLines(renderer,rendered->get_points(),rendered->get_size());
}

// void Renderer::render_text(const GraphicalText* rendered)
// {
//     SDL_RenderCopy(renderer,text_texture,NULL,&render_quad);
// }


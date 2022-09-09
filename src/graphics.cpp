#include "graphics.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

GraphicalObject::~GraphicalObject(){}

void GraphicalText::set_text(std::string text_, font_type font_)
{
    text = text_;
    font = font_;
}

// void GraphicalText::render_text(TTF_Font* font, SDL_Renderer* renderer)
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

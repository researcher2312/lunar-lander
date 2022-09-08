#include "ui.h"
#include <algorithm>

UI::UI()
{
    fonts[TITLE_FONT] = TTF_OpenFont("../resurces/oscilloscope.ttf",35);
    fonts[UI_FONT] = TTF_OpenFont("../resuorces/oscilloscope.ttf",15);
}

UI::~UI()
{
    std::for_each(fonts.begin(), fonts.end(), TTF_CloseFont);
}
void UITextElement::set_text(std::string text_, font_type font_)
{
    text = text_;
    font = font_;
}

void UITextElement::render_text(TTF_Font* font, SDL_Renderer* renderer)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,text.c_str(),color::white);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
    }
    else {
        //Create texture from surface pixels
        ui_texture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if (ui_texture == NULL){
            printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
        }
    }
    size.x = textSurface->w;
    size.y = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void UITextElement::draw(SDL_Renderer* renderer)
{
    SDL_Rect render_quad{position.x,position.y,size.x,size.y};

    //Render to screen
    SDL_RenderCopy(renderer,ui_texture,NULL,&render_quad);
}
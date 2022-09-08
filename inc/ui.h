#pragma once

#include <list>
#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"

enum font_type{
    TITLE_FONT,
    UI_FONT,
    FONT_NUM
};

namespace color
{
    constexpr SDL_Color white {255,255,255};
    constexpr SDL_Color black {0,0,0};
}

class UIElement: public GraphicalObject {
public:
    virtual void draw(SDL_Renderer*) = 0;
protected:
    SDL_Point position;
    SDL_Point size;
    SDL_Texture* ui_texture;
};

class UITextElement: public UIElement {
public:
    std::string text;
    font_type font;
    void draw(SDL_Renderer*);
    void set_text(std::string, font_type);
    void render_text(TTF_Font*, SDL_Renderer*);
private:
};

class UI {
public:
    UI();
    ~UI();
    void set_renderer(SDL_Renderer* renderer_){renderer = renderer_;};
    void draw_ui();
    void add_ui_element(UIElement*);
    std::array<TTF_Font*, FONT_NUM> fonts;

private:
    SDL_Renderer* renderer;
    std::list<UIElement*> ui_elements;
};

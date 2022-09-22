#pragma once

#include <list>
#include <SDL.h>
#include "graphics.h"



class UIElement {
public:
    SDL_Rect get_quad();
protected:
    SDL_Point position;
    SDL_Point size;
};

class UITextElement: public UIElement, public GraphicalText{
public:  
private:
};

class UI {
public:
    // void set_renderer(SDL_Renderer* renderer_){renderer = renderer_;};
    // void draw_ui();
    // void add_ui_element(UIElement*);

private:
    std::list<UIElement*> ui_elements;
};

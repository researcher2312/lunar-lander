#include "ui.h"

SDL_Rect UIElement::get_quad()
{
    SDL_Rect render_quad{position.x,position.y,size.x,size.y};
    return render_quad;
}

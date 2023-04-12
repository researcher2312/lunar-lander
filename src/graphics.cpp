#include <algorithm>
#include <iostream>
#include "graphics.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

inline SDL_Point operator+(const SDL_Point& a, const SDL_Point& b)
{
    return SDL_Point{a.x+b.x, a.y+b.y};
}

void GraphicalPoints::invoke_renderer(Renderer& renderer, SDL_Point root_position)
{
    renderer.render_points(this, root_position);
}

void GraphicalPoints::set_points(std::vector<SDL_Point>& new_points)
{
    points = std::move(new_points);
}

void GraphicalText::invoke_renderer(Renderer& renderer, SDL_Point root_position)
{
    if (m_modified) {
        renderer.render_texture_from_text(this);
        m_modified = 0;
    }
    renderer.render_text(this, root_position);
}

void GraphicalText::set_text(std::string text_, font_type font_)
{
    m_text = text_;
    m_font = font_;
    m_modified = true;
}

void GraphicalText::set_position(SDL_Point position)
{
    m_rect.x = position.x;
    m_rect.y = position.y;
}

void GraphicalText::set_size(SDL_Point position)
{
    m_rect.w = position.x;
    m_rect.h = position.y;
}

void GraphicalGeometry::invoke_renderer(Renderer& renderer, SDL_Point root_position)
{
    renderer.render_geometry(this);
}

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
    std::for_each(fonts.begin(), fonts.end(), TTF_CloseFont);
    SDL_DestroyRenderer(renderer);
    std::cerr<<"Renderer destroyed\n";
}

void Renderer::set_drawing_color(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);

}

void Renderer::render_points(const GraphicalPoints* rendered, SDL_Point root_position)
{
    std::vector<SDL_Point>relative_points(rendered->get_size());
    std::transform(rendered->get_points()->begin(),
                   rendered->get_points()->end(),
                   relative_points.begin(),
                   [root_position](const SDL_Point& position){return position+root_position;});
    set_drawing_color(rendered->get_color());
    if(rendered->points_are_connected) {
        SDL_RenderDrawLines(renderer,relative_points.data(),rendered->get_size());
    }
    else {
        SDL_RenderDrawPoints(renderer,relative_points.data(),rendered->get_size());
    }
}

void Renderer::render_text(const GraphicalText* rendered, SDL_Point)
{
    SDL_Rect destination_rect = rendered->get_quad();
    SDL_RenderCopy(renderer,textures_for_text_rendering[rendered],NULL, &destination_rect);
}

void Renderer::render_texture_from_text(GraphicalText* rendered)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(fonts[rendered->get_font()],rendered->get_text(),rendered->get_color());
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
    }
    else {
        //Create texture from surface pixels
        textures_for_text_rendering[rendered] = SDL_CreateTextureFromSurface(renderer,textSurface);
        if (textures_for_text_rendering[rendered] == NULL){
            printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
        }
    }
    SDL_Point size;
    size.x = textSurface->w;
    size.y = textSurface->h;
    rendered->set_size(size);
    SDL_FreeSurface(textSurface);
}

void Renderer::render_geometry(GraphicalGeometry* rendered)
{

}

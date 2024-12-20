#include "graphics.h"
#include "oscilloscope_ttf.h"
#include "utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>

constexpr int SCREEN_WIDTH  = 640;
constexpr int SCREEN_HEIGHT = 480;

/*!
 * @brief Sets the position of the object on screen
 *
 * The position is set in the screen coordinates
 * @param position The new position of the object
 */
void GraphicalObject::set_position(const SDL_FPoint& position)
{
    m_screen_position.x = int(position.x);
    m_screen_position.y = int(position.y);
}

void GraphicalPoints::invoke_renderer(Renderer& renderer)
{
    transform_points();
    renderer.render_points(this, m_screen_position);
}

void GraphicalPoints::set_points(std::vector<SDL_Point>& new_points)
{
    points_original = std::move(new_points);
}

/*!
 * @brief Applies rotation around root point
 *
 * The points are rotated according to internal m_rotation variable
 *
 * @param points the points which will be rotated
 */
std::vector<SDL_Point> GraphicalPoints::rotate_points(std::vector<SDL_Point> points)
{
    std::vector<SDL_Point> new_points(get_size());
    float                  angle = m_rotation;
    std::transform(points.cbegin(), points.cend(), new_points.begin(),
                   [angle](const SDL_Point& position) { return rotate_point(position, angle); });
    return new_points;
}

/*!
 * @brief Applies stretching to given GraphicalPoints
 *
 * @param stretch_x x axis stretch coefficient
 * @param stretch_y y axis stretch coefficient
 */
std::vector<SDL_Point> GraphicalPoints::stretch_points(std::vector<SDL_Point> points)
{
    auto                   stretch = m_stretch;
    std::vector<SDL_Point> new_points(get_size());
    std::transform(points.cbegin(), points.cend(), new_points.begin(),
                   [stretch](const SDL_Point& position) {
                       return stretch_point(position, stretch.x, stretch.y);
                   });
    return new_points;
}

/*!
 * @brief Applies all designed transformations to original point matrix
 *
 */
void GraphicalPoints::transform_points()
{
    points_transformed = rotate_points(stretch_points(points_original));
}

void GraphicalText::invoke_renderer(Renderer& renderer)
{
    if (m_modified) {
        renderer.render_texture_from_text(this);
        m_modified = 0;
    }
    renderer.render_text(this, m_screen_position);
}

/*!
 * @brief Sets the displayed text to given string
 *
 * @param text The text to be displayed
 * @param font The font to be used
 */
void GraphicalText::set_text(std::string text, font_type font)
{
    m_text     = text;
    m_font     = font;
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

void GraphicalGeometry::invoke_renderer(Renderer& renderer) { renderer.render_geometry(this); }

Renderer::Renderer(SDL_Window* window)
{
    SDL_RWops* font_raw_data  = SDL_RWFromConstMem(oscilloscope_ttf_start, oscilloscope_ttf_size);
    SDL_RWops* font_raw_data2 = SDL_RWFromConstMem(oscilloscope_ttf_start, oscilloscope_ttf_size);
    fonts[TITLE_FONT]         = TTF_OpenFontRW(font_raw_data, 1, 35);
    fonts[UI_FONT]            = TTF_OpenFontRW(font_raw_data2, 1, 15);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    set_drawing_color(color::white);
    SDL_RenderClear(renderer);
}

Renderer::~Renderer()
{
    std::for_each(fonts.begin(), fonts.end(), TTF_CloseFont);
    SDL_DestroyRenderer(renderer);
    std::cerr << "Renderer destroyed\n";
}

void Renderer::set_drawing_color(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Renderer::render_points(const GraphicalPoints* rendered, SDL_Point root_position)
{
    std::vector<SDL_Point> relative_points(rendered->get_size());
    std::transform(rendered->get_points().cbegin(), rendered->get_points().cend(),
                   relative_points.begin(),
                   [root_position](const SDL_Point& position) { return position + root_position; });
    set_drawing_color(rendered->get_color());
    if (rendered->points_are_connected) {
        SDL_RenderDrawLines(renderer, relative_points.data(), rendered->get_size());
    }
    else {
        SDL_RenderDrawPoints(renderer, relative_points.data(), rendered->get_size());
    }
}

void Renderer::render_text(const GraphicalText* rendered, SDL_Point)
{
    SDL_Rect destination_rect = rendered->get_quad();
    SDL_RenderCopy(renderer, textures_for_text_rendering[rendered], NULL, &destination_rect);
}

void Renderer::render_texture_from_text(GraphicalText* rendered)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(fonts[rendered->get_font()],
                                                    rendered->get_text(), rendered->get_color());
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    else {
        // Create texture from surface pixels
        textures_for_text_rendering[rendered] = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textures_for_text_rendering[rendered] == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
    }
    SDL_Point size;
    size.x = textSurface->w;
    size.y = textSurface->h;
    rendered->set_size(size);
    SDL_FreeSurface(textSurface);
}

void Renderer::render_geometry(GraphicalGeometry* rendered) {}

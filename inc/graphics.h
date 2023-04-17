#pragma once

#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>

enum font_type{
    TITLE_FONT,
    UI_FONT,
    FONT_NUM
};

namespace color
{
    constexpr SDL_Color white {255,255,255};
    constexpr SDL_Color black {0,0,0};
    constexpr SDL_Color red {255,0,0};
    constexpr SDL_Color green {0,255,0};
    constexpr SDL_Color blue {0,0,255};
}
class Renderer;

class GraphicalObject {
public:
    virtual void invoke_renderer(Renderer&, SDL_Point)=0;
    void set_color(SDL_Color color){m_color=color;};
    SDL_Color get_color() const{return m_color;};
private:
    SDL_Color m_color;
};

class GraphicalPoints: public virtual GraphicalObject {
public:
    GraphicalPoints(bool connected): points_are_connected(connected){};
    void invoke_renderer(Renderer&, SDL_Point) override final;
    const std::vector<SDL_Point>& get_points() const {return points;};
    void set_points(std::vector<SDL_Point>&);
    auto get_size() const{return points.size();};
    bool points_are_connected;
protected:
    std::vector<SDL_Point> points;
    std::vector<SDL_Point> points_relative;
};

class GraphicalText: public virtual GraphicalObject {
public:
    SDL_Rect get_quad() const {return m_rect;};
    void set_position(SDL_Point);
    void set_size(SDL_Point);
    void invoke_renderer(Renderer&, SDL_Point) override final;
    void set_text(std::string, font_type);
    auto get_text() const {return m_text.c_str();};
    font_type get_font() const {return m_font;};
protected:
    SDL_Rect m_rect;
    bool m_modified;
    std::string m_text;
    font_type m_font;
};

class GraphicalGeometry: public virtual GraphicalObject {
public:
    void invoke_renderer(Renderer&, SDL_Point) override final;
    // auto get_vertex() const{return vertex.data();};
    // auto get_size() const{return vertex.size();};
protected:
    // std::vector<SDL_Point> vertex;
};

class Renderer {
public:
    Renderer(SDL_Window*);
    ~Renderer();
    void set_drawing_color(const SDL_Color&);
    void clear_screen() const {SDL_RenderClear(renderer);};
    void show_screen() const {SDL_RenderPresent(renderer);};
    void render_points(const GraphicalPoints*, SDL_Point);
    void render_text(const GraphicalText*, SDL_Point);
    void render_texture_from_text(GraphicalText*);
    void render_geometry(GraphicalGeometry*);
private:
    SDL_Renderer* renderer;
    std::array<TTF_Font*, FONT_NUM> fonts;
    std::unordered_map<const GraphicalText*, SDL_Texture*> textures_for_text_rendering; 
};

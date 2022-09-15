#pragma once

#include <vector>
#include <string>
#include <array>
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
    virtual void invoke_renderer(Renderer&)=0;
    void setColor(SDL_Color color){m_color=color;};
    SDL_Color getColor() const{return m_color;};
private:
    SDL_Color m_color;
};

class GraphicalPoints: public virtual GraphicalObject {
public:
    void invoke_renderer(Renderer&) override;
    auto get_points() const{return points.data();};
    auto get_size() const{return points.size();};
protected:
    std::vector<SDL_Point> points;
};

class GraphicalLines: public virtual GraphicalObject {
public:
    void invoke_renderer(Renderer&) override;
    auto get_points() const{return points.data();};
    auto get_size() const{return points.size();};

protected:
    std::vector<SDL_Point> points;
};

class GraphicalText: public virtual GraphicalObject {
public:
    void set_text(std::string, font_type);
    void invoke_renderer(Renderer&) override;
protected:
    bool modified;
    std::string text;
    font_type font;
    SDL_Texture* text_texture;
};

class Renderer {
public:
    Renderer(SDL_Window*);
    ~Renderer();
    void set_drawing_color(const SDL_Color&);
    void clear_screen() const {SDL_RenderClear(renderer);};
    void show_screen() const {SDL_RenderPresent(renderer);};
    void render_line(const GraphicalLines*);
    void render_points(const GraphicalPoints*);
    // void render_text(const GraphicalText*);
private:
    SDL_Renderer* renderer;
    std::array<TTF_Font*, FONT_NUM> fonts;
};

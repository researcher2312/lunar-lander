#pragma once

#include <vector>
#include <string>
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

class GraphicalObject {
public:
    virtual ~GraphicalObject() = 0;
    void setColor(SDL_Color color){m_color=color;};
    SDL_Color getColor() const{return m_color;};
private:
    SDL_Color m_color;
};

class GraphicalPoints: public virtual GraphicalObject {
public:
    auto get_points() const{return points.data();};
protected:
    std::vector<SDL_Point> points;
};

class GraphicalLines: public virtual GraphicalPoints {
public:
private:
};

class GraphicalText: public virtual GraphicalObject {
public:
    void set_text(std::string, font_type);
protected:
    // void render_text(TTF_Font* font, SDL_Renderer* renderer);
    std::string text;
    font_type font;
    SDL_Texture* ui_texture;
};

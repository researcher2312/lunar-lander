#pragma once

#include <SDL.h>

constexpr SDL_Point ROOT_ZERO{0,0};
constexpr SDL_FPoint FROOT_ZERO{0.0,0.0};

inline SDL_Point operator+(const SDL_Point& a, const SDL_Point& b)
{
    return SDL_Point{a.x+b.x, a.y+b.y};
}

inline SDL_FPoint operator+(const SDL_FPoint& a, const SDL_FPoint& b)
{
    return SDL_FPoint{a.x+b.x, a.y+b.y};
}

inline SDL_FPoint operator/(const SDL_FPoint& a, int b)
{
    return SDL_FPoint{a.x/b, a.y/b};
}

inline SDL_FPoint operator*(const float& a, const SDL_FPoint& b)
{
    return SDL_FPoint{b.x*a, b.y*a};
}

SDL_Point rotate_point(const SDL_Point point, float angle);
SDL_FPoint rotate_point(const SDL_FPoint point, float angle);
#include "utils.h"

SDL_Point rotate_point(const SDL_Point point, float angle)
{
    return SDL_Point{int(point.x*cos(angle)-point.y*sin(angle)),
                     int(point.y*cos(angle)+point.x*sin(angle))};
}

SDL_FPoint rotate_point(const SDL_FPoint point, float angle)
{
    return SDL_FPoint{point.x*cos(angle)-point.y*sin(angle),
                     point.y*cos(angle)+point.x*sin(angle)};
}
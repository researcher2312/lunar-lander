#pragma once

#include <SDL.h>
#include "graphics.h"

class GameObject {
public:
    virtual void draw(Renderer&)=0;
    virtual void update(float)=0;
};


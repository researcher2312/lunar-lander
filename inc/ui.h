#pragma once

#include <list>
#include <SDL.h>
#include "graphics.h"
#include "game_object.h"

class UI: public GameObject {
public:
    UI();
    ~UI();
    void draw(Renderer&) override;
private:
    std::vector<GraphicalText*> ui_elements;
};

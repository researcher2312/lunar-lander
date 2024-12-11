#pragma once

#include "game_object.h"
#include "graphics.h"
#include <SDL.h>
#include <list>

class UI: public GameObject {
  public:
    UI();
    ~UI();
    void draw(Renderer&) override;
    void update(float) override;

  private:
    std::vector<GraphicalText*> ui_elements;
};

#pragma once

#include <SDL.h>
#include "game_objects.h"

class Game {
public:
    Game();
    ~Game();
    void start();
    void finish();
    void update();
    void get_user_input();
private:
    GameWindow window;
};

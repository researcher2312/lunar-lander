#pragma once

#include <SDL.h>
#include "graphics.h"



/*!
 * @brief Interface for receiving keyboard signals
 * 
 * The object can receive two kinds of signals, one is sent on key press
 * and the other one on key release.
 */
class SignalReceiver {
public:
    virtual void receive_key_press(SDL_Keycode)=0;
    virtual void receive_key_release(SDL_Keycode)=0;
};

/*!
 * @brief Template for building various objects in game
 * 
 */
class GameObject {
public:
    virtual void draw(Renderer&)=0;
    virtual void update(float)=0;
};


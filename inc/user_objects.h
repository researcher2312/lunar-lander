#pragma once

#include "graphics.h"
#include "physics.h"
#include "game_object.h"

constexpr int STAR_COUNT = 80;
constexpr int HILLS_COUNT = 200;

class BackgroundImage: public GameObject {
public:
    BackgroundImage();
    virtual ~BackgroundImage();
    void draw(Renderer& renderer) override;
    void update(float) override;
private:
    GraphicalPoints* stars;
    void generate_random_stars();
};

class Terrain: public GameObject {
public:
    Terrain();
    virtual ~Terrain();
    void draw(Renderer& renderer) override;
    void update(float) override;
private:
    GraphicalPoints* hills;
    void generate_random_terrain();
};

class Lander: public GameObject, public SignalReceiver {
public:
    Lander();
    virtual ~Lander();
    void draw(Renderer& renderer) override;
    void update(float) override;
    void receive_key_press(SDL_Keycode) override;
    void receive_key_release(SDL_Keycode) override;
private:
    bool engine_on;
    int engine_flame_percent;
    GraphicalPoints* chassis;
    GraphicalPoints* flame;
    RigidBody* physics;
};

#pragma once

#include <list>
#include <SDL.h>
#include "game_object.h"

constexpr SDL_FPoint G_FORCE{0, 10};
constexpr SDL_FPoint FPOINT_ZERO{0,0};

class Timer{
public:
    Timer();
    void start();
    void stop();
    Uint32 get_ticks();
    bool is_started() const {return m_started;};
private:
    Uint32 m_start_ticks;
    bool m_started;
};

class PhysicalObject {
public:
    void update(float dt);
    bool collisions_enabled;
};

//use basic SI units
class RigidBody {
public:
    RigidBody(int mass_kg);
    void set_position(SDL_FPoint);
    SDL_FPoint get_position()const {return m_position_m;}
    void set_speed(SDL_FPoint);
    void move(SDL_FPoint);
    void rotate(int);
    void set_rotation(int);
    void set_rotation_speed(int);
    void apply_force(SDL_FPoint);
    void update(float time);
protected:
    bool m_gravity_enabled;
    SDL_FPoint m_position_m;
    int m_mass_kg;
    int m_rotation_inertia_kg_m;
    float m_rotation;
    SDL_FPoint m_speed_m_s;
    float m_rotation_speed;
    SDL_FPoint m_overall_force_N;
};

class Physics {
public:
    Physics();
    void tick();
    void add_new_physical_object(GameObject*);
private:
    unsigned int m_previous_frame_ticks;
    void update_physics(float frame_duration);
    void check_collisions();
    std::list<GameObject*> m_physical_objects;
};

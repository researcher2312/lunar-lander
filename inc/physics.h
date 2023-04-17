#pragma once

#include <list>
#include <SDL.h>
#include "game_object.h"

constexpr SDL_Point G_FORCE{0, 10};

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

//use basic SI units
class PhysicalObject {
public:
    PhysicalObject(int mass_kg);
    void set_position(SDL_Point);
    void set_speed(SDL_Point);
    void move(SDL_Point);
    void rotate(int);
    void set_rotation(int);
    void set_rotation_speed(int);
    void apply_force(SDL_Point);
    void update();
protected:
    bool m_gravity_enabled;
    SDL_Point m_position_m;
    int m_mass_kg;
    int m_rotation_inertia_kg_m;
    int m_rotation;
    SDL_Point m_speed_m_s;
    int m_rotation_speed;
    SDL_Point m_overall_force_N;
};

class Physics {
public:
    void tick(int);
    void add_new_physical_object(GameObject*);
private:
    unsigned int m_previous_frame_ticks;
    void update_physics();
    void check_collisions();
    std::list<GameObject*> m_physical_objects;

};

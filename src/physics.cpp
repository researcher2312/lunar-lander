#include "physics.h"

Timer::Timer()
{
    m_start_ticks = 0;
    m_started = false;
}

void Timer::start()
{
    m_started = true;
    m_start_ticks = SDL_GetTicks();
}

void Timer::stop()
{
    m_started = false;
    m_start_ticks = 0;
}

Uint32 Timer::get_ticks()
{
    if (m_started) {
        return SDL_GetTicks() - m_start_ticks;
    }
    else {
        return 0;
    }
}

inline SDL_Point operator+(const SDL_Point& a, const SDL_Point& b)
{
    return SDL_Point{a.x+b.x, a.y+b.y};
}

PhysicalObject::PhysicalObject(int mass_kg = 0)
{
    m_mass_kg = mass_kg;
    m_gravity_enabled = true;
}

void PhysicalObject::update()
{
    if (m_gravity_enabled) {
        apply_force(G_FORCE);
    }
    // m_speed_m_s += tick*m_overall_force/m_mass_kg;


}

void PhysicalObject::set_position(SDL_Point position)
{
    m_position_m = position;
}

void PhysicalObject::set_speed(SDL_Point speed)
{
    m_speed_m_s = speed;
}

void PhysicalObject::move(SDL_Point movement)
{
    m_position_m = m_position_m+movement;
}

void PhysicalObject::set_rotation(int rotation)
{
    m_rotation = rotation;
}

void PhysicalObject::set_rotation_speed(int rotation_speed)
{
    m_rotation_speed = rotation_speed;
}

void PhysicalObject::apply_force(SDL_Point force)
{
    m_overall_force_N = m_overall_force_N+force;
}

// Physics::Physics()
// {

// }

// Physics::~Physics()
// {

// }

void Physics::update_physics()
{

    m_previous_frame_ticks = SDL_GetTicks();
}

void Physics::add_new_physical_object(GameObject* new_object)
{
    m_physical_objects.push_back(new_object);
}

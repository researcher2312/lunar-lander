#include "physics.h"

Timer::Timer()
{
    m_start_ticks = 0;
    m_started = false;
}

void PhysicalObject::set_position(SDL_Point position)
{
    m_position = position;
}

void PhysicalObject::set_speed(SDL_Point speed)
{
    m_speed = speed;
}

void PhysicalObject::move(SDL_Point movement)
{
    m_position += movement;
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
    m_overall_force += force;
}

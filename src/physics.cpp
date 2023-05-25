#include <iostream>
#include "utils.h"
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

/*!
 * @brief Construct a new Rigid Body:: Rigid Body object
 * 
 * @param mass_kg 
 */
RigidBody::RigidBody(int mass_kg = 0)
{
    m_position_m = FROOT_ZERO;
    m_mass_kg = mass_kg;
    m_rotation = 0;
    m_speed_m_s = FPOINT_ZERO;
    m_rotation_speed = 0;
    m_overall_force_N = FPOINT_ZERO;
    m_gravity_enabled = true;
}

/*!
 * @brief Update the rigidbody's physics, using the time that has passed since
 * the last frame
 * 
 * @param time the time that has passed since the last frame
 */
void RigidBody::update(float time)
{
    if (m_gravity_enabled) {
        apply_force(G_FORCE);
    }

    std::cerr << "Time:" << time;
    std::cerr << " Force:" << m_overall_force_N.y;
    m_speed_m_s = m_speed_m_s + time*m_overall_force_N/m_mass_kg;
    std::cerr << " Speed:" << m_speed_m_s.y;
    m_position_m = m_position_m + time*m_speed_m_s;
    std::cerr << " Position:" << m_position_m.y << '\n';
    m_overall_force_N = FPOINT_ZERO;
}

void RigidBody::set_position(SDL_FPoint position)
{
    m_position_m = position;
}

void RigidBody::set_speed(SDL_FPoint speed)
{
    m_speed_m_s = speed;
}

void RigidBody::move(SDL_FPoint movement)
{
    m_position_m = m_position_m+movement;
}

/**
 * @brief 
 * 
 * @param rotation 
 */
void RigidBody::set_rotation(int rotation)
{
    m_rotation = rotation;
}

/*!
 * @brief Set rotation speed
 * 
 * @param rotation_speed 
 */
void RigidBody::set_rotation_speed(int rotation_speed)
{
    m_rotation_speed = rotation_speed;
}

/*!
 * @brief Apply fore to the rigidbody
 *
 * The force is deleted in the next physics update
 * 
 * @param force 
 */
void RigidBody::apply_force(SDL_FPoint force)
{
    m_overall_force_N = m_overall_force_N+force;
}

Physics::Physics()
{
    m_previous_frame_ticks = 0;
}

// Physics::~Physics()
// {

// }

void Physics::tick()
{
    auto current_ticks = SDL_GetTicks() - m_previous_frame_ticks;
    update_physics(current_ticks/1000.f);
    m_previous_frame_ticks = SDL_GetTicks();

}

/*!
 * @brief Update the physics system after duration of the frame
 * 
 * @param frame_duration 
 */
void Physics::update_physics(float frame_duration)
{
    for (auto &rendered_object: m_physical_objects) {
        rendered_object->update(frame_duration);
    }
}

void Physics::add_new_physical_object(GameObject* new_object)
{
    m_physical_objects.push_back(new_object);
}

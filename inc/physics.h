#pragma once

#include "game_object.h"
#include <SDL.h>
#include <list>

constexpr SDL_FPoint G_FORCE{0, 10};
constexpr SDL_FPoint FPOINT_ZERO{0, 0};

/*!
 * @brief Timer to measure milisecond timespans
 *
 */
class Timer {
  public:
    Timer();
    void   start();
    void   stop();
    Uint32 get_ticks();
    bool   is_started() const { return m_started; };

  private:
    Uint32 m_start_ticks;
    bool   m_started;
};

/*!
 * @brief Abstract representation of any physical body
 *
 */
class PhysicalObject {
  public:
    virtual void update(float dt) = 0;
    bool         collisions_enabled;
};

/*!
 * @brief Representation of rigid, point-size body
 *
 * The physics simulation is calculated as though the body was a size
 * of a point, concentrating the mass in this point. The collider can represent
 * any other shape, but the body stays the size of a single point.
 *
 * All units in class represent SI units.
 */
class RigidBody: public PhysicalObject {
  public:
    RigidBody(int mass_kg);
    void       set_position(SDL_FPoint);
    SDL_FPoint get_position() const { return m_position_m; }
    void       set_speed(SDL_FPoint);
    void       move(SDL_FPoint);
    void       rotate(int);
    void       set_rotation(float);
    float      get_rotation() const { return m_rotation; };
    void       set_rotation_speed(float);
    void       apply_force(SDL_FPoint);
    void       update(float dt);

  protected:
    bool       m_gravity_enabled;
    int        m_mass_kg;
    int        m_rotation_inertia_kg_m;
    float      m_rotation_speed;
    float      m_rotation;
    SDL_FPoint m_speed_m_s;
    SDL_FPoint m_position_m;
    SDL_FPoint m_overall_force_N;
};

/*!
 * @brief Class to handle all physics interactions
 *
 */
class Physics {
  public:
    Physics();
    void tick();
    void add_new_physical_object(GameObject*);

  private:
    unsigned int           m_previous_frame_ticks;
    void                   update_physics(float frame_duration);
    void                   check_collisions();
    std::list<GameObject*> m_physical_objects;
};

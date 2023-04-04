#include <list>
#include <SDL.h>

class Timer{
public:
    Timer();
    void start();
    void stop();
    Uint32 getTicks();
    bool isStarted() const {return m_started;};
private:
    Uint32 m_start_ticks;
    bool m_started;
};

//use basic SI units
class PhysicalObject {
public:
    void set_position(SDL_Point);
    void set_speed(SDL_Point);
    void move(SDL_Point);
    void rotate(int);
    void set_rotation(int);
    void set_rotation_speed(int);
    void apply_force(SDL_Point, SDL_Point);
protected:
    bool gravity_enabled;
    int m_weight;
    int m_rotation_inertia;
    SDL_Point m_position;
    int m_rotation;
    SDL_Point m_speed;
    int m_rotation_speed;
    SDL_Point m_overall_force;
};

class Physics {
public:
    void tick(int);
private:
    void update_physics();
    void check_collisions();
    std::list<PhysicalObject*> m_physical_objects;

};

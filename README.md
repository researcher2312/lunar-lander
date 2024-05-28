# Lunar Lander
Lunar Lander game clone from Atari arcade machine

[Wiki](https://en.wikipedia.org/wiki/Lunar_Lander_(1979_video_game))

Built using C++, SDL2, and Cmake.
An educational project to better learn object oriented programming and design patterns.



## Install instructions:
1. Clone the repository.
2. Install dependencies using Conan.

```bash
conan install . --build=missing
```
for a debug version you can add `--settings=build_type=Debug`

3. Configure and build the project with CMake.

```bash
cmake --preset conan-release
cmake --build --preset conan-release
```

for a debug version you can use `conan-debug`

4. Run the executable.

```bash
./build/Release/lunar-lander
```

## Proposed class diagram:

```mermaid
classDiagram 

class PhysicalObject{
    <<interface>>
    # m_collisions_enabled: bool
    + update(float dt)
}

class RigidBody{
    #m_gravity_enabled: bool
    #m_weight: int
    #m_rotation_inertia: float
    #m_position: SDL_FPoint
    #m_rotation: float
    #m_speed: SDL_FPoint
    #m_rotation_speed: float
    #m_overall_force: SDL_FPoint
    +set_position()
    +set_speed()
    +move()
    +rotate()
    +set_rotation()
    +set_rotation_speed()
    +apply_force()
}

class StaticObject{
pass
}

class GraphicalObject{
    <<interface>>
    -color: SDL_Color
    +set_color()
    +get_color()
    + invoke_render(Renderer&)
}

class GraphicalPoints{
    +points_are_connected: bool
    +invoke_renderer(Renderer&)
    +get_points() const: SDL_Point*
    +set_points(&vector<SDL_Point>)
    +get_size(): int
    -points: vector<SDL_Point>

}

class GraphicalText{
    #m_rect: SDL_Rect
    #m_modified: bool
    #text: string
    #font: font_type
    +get_quad()
    +set_position()
    +set_size()
    +invoke_renderer(Renderer&)
    +set_text(string, font_type)
    +get_text()
    +get_font
}

class GraphicalBitmap{
pass
}

class GameObject{
    <<interface>>
    +draw(SDL_Renderer*)
    +update(float dt)
}

class Game{
    +Game()
    +~Game()
    +start()
    +finish()
    +get_user_input()
    +update()
}

class GameWindow{
    +GameWindow()
    +~GameWindow()
    -graphical_objects: list<GameObjects>
    -SDL_Window
    -renderer: unique_ptr<Renderer>
    +update_graphics()
    +add_new_graphical_object()
    
}

class Renderer{
    +Renderer(SDL_Window*)
    +~Renderer()
    +set_drawing_color(SDL_Color)
    +clear_screen()
    +show_screem()
    +render_line(GraphicalLines*)
    +render_text(GraphicalText*)
    -renderer: SDL_Renderer*
    -fonts: array
    -textures_for_text_rendering: unordered_map
}

class InputHandler{
    +subscribe_action()
    +delete_action()
    +handle_game_input()
}

class Player{
    +points
    +add_points()
    +evaluate_landing()
}

class Physics{
    -physical_objects: list
    +update_physics()
    -check_collisions()
}

class UI{
    +draw()
    -ui_elements: vector
}

Game *-- Physics
Game *-- Player
Game *-- GameWindow
Game *-- UI
GameWindow *-- Renderer
GameWindow *-- InputHandler

PhysicalObject <|-- RigidBody
PhysicalObject <|-- StaticObject

GraphicalObject <|.. GraphicalPoints
GraphicalObject <|.. GraphicalText
GraphicalObject <|.. GraphicalBitmap

GameObject <|-- UI
UI *-- GraphicalText
```

cmake_minimum_required(VERSION 3.10)

project(lunar-lander VERSION 0.1
		     LANGUAGES CXX)

find_package(SDL2_ttf REQUIRED)
find_package(SDL2 REQUIRED)


set(SOURCES
    src/main.cpp
    src/game.cpp
    src/game_object.cpp
    src/user_objects.cpp
    src/graphics.cpp
    src/ui.cpp
    src/physics.cpp
    src/utils.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb -Wall")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} sdl_ttf::sdl_ttf SDL2::SDL2main)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
)

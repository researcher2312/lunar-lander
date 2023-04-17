cmake_minimum_required(VERSION 3.10)

project(lunar-lander VERSION 0.1
		     LANGUAGES CXX)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

# find_package(SDL2 REQUIRED)
# find_package(SDL2_ttf REQUIRED)

set(SOURCES
    src/main.cpp
    src/game.cpp
    src/game_object.cpp
    src/user_objects.cpp
    src/graphics.cpp
    src/ui.cpp
    src/physics.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
)

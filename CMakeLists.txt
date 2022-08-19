cmake_minimum_required(VERSION 3.10)

project(lunar-lander VERSION 0.1
		     LANGUAGES CXX)

find_package(SDL2 REQUIRED)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(lander PRIVATE cxx_std_17)

target_include_directories(lander PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(lander PRIVATE ${SDL2_LIBRARIES})

target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

#add_subdirectory(src)


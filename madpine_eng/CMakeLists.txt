cmake_minimum_required(VERSION 3.22)
project(madpine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/flecs-3.1.0)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)
add_subdirectory(deps/glew/build/cmake)

file(GLOB_RECURSE madpine_SRC
        "Source/**.h"
        "Source/**.cpp"
        )

add_library(madpine SHARED ${madpine_SRC})

target_include_directories(madpine PUBLIC
        deps/flecs-3.1.0/include
        deps/glfw/include
        deps/glew/include
        deps/stb)

target_link_libraries(madpine flecs
        glfw
        glew
        glm
        opengl32)



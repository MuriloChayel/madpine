cmake_minimum_required(VERSION 3.22)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(madpine_eng)

add_executable(sandbox main.cpp)

target_include_directories(sandbox PUBLIC ${CMAKE_SOURCE_DIR}/madpine_eng)

target_link_libraries(sandbox madpine)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/madpine_eng/libmadpine.dll" "${CMAKE_BINARY_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/bin/glew32d.dll" "${CMAKE_BINARY_DIR}"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/madpine_eng/Shaders" "${CMAKE_BINARY_DIR}/Shaders"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/Sprites" "${CMAKE_BINARY_DIR}/Sprites"

        )

cmake_minimum_required(VERSION 3.26)
project(Game_Engine)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        Dependencies/glad/glad.c
        main.cpp
        callbacks.h
        Utilities.h
        rendering/GL/Draw.h
        Input.h
        rendering/GL/ShaderLoader.h
        rendering/GL/MeshLoader.h
        rendering/GL/DrawDetails.h
        rendering/GL/QueryAttribs.h)


include_directories(Dependencies)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib-mingw-w64/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include")
target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(Game_Engine OpenGL::GL)

add_library(glad Dependencies/glad/glad.c)
target_link_libraries(${PROJECT_NAME} glad)

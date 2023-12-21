#pragma once
#include "fstream"
#include <chrono>

static void write_log(const char* s){
    std::ofstream logs;
//    printf("Log created\n");
    logs.open("logs.lore", std::ofstream::app | std::ofstream::out);
    logs << std::chrono::system_clock::now() << " " << s << "\n";
    logs.close();
}

void logGLinfo(){
    const GLubyte* vendor = glGetString(GL_VENDOR);
    printf("GL Vendor : %s\n", vendor);
    write_log("GL Vendor : ");
    write_log(reinterpret_cast<const char *>(vendor));

    const GLubyte* renderer = glGetString(GL_RENDERER);
    printf("GL Renderer : %s\n", renderer);
    write_log("GL Renderer : ");
    write_log(reinterpret_cast<const char *>(renderer));

    const GLubyte* version = glGetString(GL_VERSION);
    printf("GL Version : %s\n", version);
    write_log("GL Version : ");
    write_log(reinterpret_cast<const char *>(version));

    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GLSL Version : %s\n", glslVersion);
    write_log("GLSL Version : ");
    write_log(reinterpret_cast<const char *>(glslVersion));
}
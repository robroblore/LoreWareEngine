#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utilities.h"
#include "callbacks.h"
#include "rendering/GL/DrawDetails.h"
#include "rendering/GL/Draw.h"
#include "rendering/GL/MeshLoader.h"
#include "rendering/GL/QueryAttribs.h"
#include "rendering/GL/ShaderLoader.h"
#include "Input.h"
#include <random>

int main(int argc, char** argv)
{
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(1280, 960, "LoreWare Engine", nullptr, nullptr);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

//    logGLinfo();

    //Callbacks
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
    glfwSetWindowCloseCallback(window, glfw_window_close_callback);

    //Shader Programs
    const char* vertshader =
            "#version 460 core \n"
            "layout(location = 0) in vec3 vertPos; \n"
            "layout(location = 1) in vec3 vertColor; \n"
            "layout(location = 0) out vec4 fragColor; \n"
            "void main(){ \n"
            "  fragColor = vec4(vertColor, 1.0); \n"
            "  gl_Position = vec4(vertPos, 1.0); \n"
            "}";

    const char* fragshader =
            "#version 460 core \n"
            "layout(location = 0) in vec4 fragColor; \n"
            "out vec4 color; \n"
            "void main(){ \n"
            "color = fragColor; \n"
            "}";

    unsigned int mainShader = LoadShader(vertshader, fragshader);

    //Draw buffers
    glClearColor(.53f, .81f, .92f, 1.f);
    std::vector<DrawDetails> Balls;{
        //Create object to display points
        const float posData[] = {
                //Ball left
                -.8f, -.5f, 0.f,
                -.8f, -.9f, 0.f,
                -.5f, -.5f, 0.f,
                -.5f, -.9f, 0.f,
                // Ball right
                -.4f, -.5f, 0.f,
                -.4f, -.9f, 0.f,
                -.1f, -.5f, 0.f,
                -.1f, -.9f, 0.f
        };

        const float colorData[] ={
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f
        };

        const GLuint elems[] = {0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7};

        Balls.push_back(UploadMesh(posData, colorData, sizeof(posData) / sizeof(posData[0]), elems, sizeof(elems) / sizeof(elems[0])));
    }

    std::vector<DrawDetails> Penis;{
        const float posData[] = {
                -.6f, .3f, 0.f,
                -.6f, -.7f, 0.f,
                -.3f, .3f, 0.f,
                -.3f, -.7f, 0.f
        };

        const float colorData[] ={
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
        };

        const GLuint elems[] = {0, 1, 2, 1, 2, 3};

        Penis.push_back(UploadMesh(posData, colorData, sizeof(posData) / sizeof(posData[0]), elems, sizeof(elems) / sizeof(elems[0])));
    }

//    QueryAttribs(Balls.back().vao);
    /* Loop until the user closes the window */
    while(!glfwWindowShouldClose(window)){
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(mainShader);
        Draw(Balls);

        Draw(Penis);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    UnloadMesh(Balls);
//    UnloadMesh(Penis);
    glfwTerminate();
    return 0;
}
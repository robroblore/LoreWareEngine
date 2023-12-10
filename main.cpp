#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "callbacks.h"
#include "Utilities.h"
#include "vertex.h"
#include "rendering/OpenGlLoader.h"
#include "rendering/OpenGlDraw.h"
#include "rendering/GLSLShaderLoader.h"
#include "Input.h"
#include <random>

int main(int argc, char** argv)
{
    GLFWwindow* window;
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "LoreWare Engine", nullptr, nullptr);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    //logGLinfo();
    //Callbacks
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
    glfwSetWindowCloseCallback(window, glfw_window_close_callback);

    //Shader Programs
    const char* vertshader =
            "#version 460 core                                                  \n"
            "layout(location = 0) in vec3 vertexPosition_modelspace;            \n"
            //"uniform mat4 modelmatrix;                                          \n"
            "void main(){                                                       \n"
            //"  gl_Position = modelmatrix * vec4(vertexPosition_modelspace, 1.0);\n"
            "  gl_Position = vec4(vertexPosition_modelspace, 1.0);\n"
            "}";
    const char* fragshaderBlack =
            "#version 460 core   \n"
            "out vec3 color;     \n"
            "uniform vec3 ucolor = vec3(0.,0.,0.);\n"
            "void main() {       \n"
            "  color = ucolor;   \n"
            "}";
    const char* fragshaderRed =
            "#version 460 core   \n"
            "out vec3 color;     \n"
            "uniform vec3 ucolor = vec3(1.,0.,0.);\n"
            "void main() {       \n"
            "  color = ucolor;   \n"
            "}";

    unsigned int mainShaderB = LoadShader(vertshader, fragshaderBlack);
    unsigned int mainShaderR = LoadShader(vertshader, fragshaderRed);

    //Draw buffers
    glClearColor(.53f, .81f, .92f, 1.f);
    std::vector<DrawDetails> Balls;{
        //Create object to display points
        std::vector<Vertex> obj_pts;
        //ball left
        obj_pts.emplace_back(-.8f, -.5f, 0.f);
        obj_pts.emplace_back(-.8f, -.9f, 0.f);
        obj_pts.emplace_back(-.5f, -.5f, 0.f);
        obj_pts.emplace_back(-.5f, -.9f, 0.f);
        //ball right
        obj_pts.emplace_back(-.4f, -.5f, 0.f);
        obj_pts.emplace_back(-.4f, -.9f, 0.f);
        obj_pts.emplace_back(-.1f, -.5f, 0.f);
        obj_pts.emplace_back(-.1f, -.9f, 0.f);


        std::vector<uint32_t> elem = {0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7};

        Balls.push_back(UploadMesh(obj_pts, elem));
    }

    std::vector<DrawDetails> Penis;{
        //Create object to display points
        std::vector<Vertex> obj_pts;

        obj_pts.emplace_back(-.6f, .3f, 0.f);
        obj_pts.emplace_back(-.6f, -.7f, 0.f);
        obj_pts.emplace_back(-.3f, .3f, 0.f);
        obj_pts.emplace_back(-.3f, -.7f, 0.f);
        std::vector<uint32_t> elem = {0, 1, 2, 1, 2, 3};

        Penis.push_back(UploadMesh(obj_pts, elem));
    }

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.f, 1.f);


    /* Loop until the user closes the window */

    while(!glfwWindowShouldClose(window)){
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(mainShaderR);
        Draw(Balls);

        glUseProgram(mainShaderB);
        float c1 = distribution(generator);
        float c2 = distribution(generator);
        float c3 = distribution(generator);
        uint32_t var2 = glGetUniformLocation(mainShaderB, "ucolor");
        glUniform3f(var2, c1, c2, c3);
        Draw(Penis);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    UnloadMesh(Balls);
    UnloadMesh(Penis);
    glfwTerminate();
    return 0;
}
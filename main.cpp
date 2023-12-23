#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utilities.h"
#include "callbacks.h"
#include "rendering/GL/DrawDetails.h"
#include "rendering/GL/Draw.h"
#include "rendering/GL/MeshLoader.h"
#include "rendering/GL/QueryShader.h"
#include "rendering/GL/ShaderLoader.h"
#include "Input.h"
#include <random>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>


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
    std::string vertshader = ReadToString("../shaders/VertexShader.glsl");
    std::string fragshader = ReadToString("../shaders/FragmentShader.glsl");
    unsigned int mainShader = LoadShader(vertshader.c_str(), fragshader.c_str());

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

    QueryInputAttribsAndUniforms(mainShader);

    /* Loop until the user closes the window */
    double prev_time = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
        double current_time = glfwGetTime();
        double deltaTime = current_time - prev_time;
        prev_time = current_time;
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(mainShader);
        glm::mat4 finalModelMatrix = glm::mat4(1);
        finalModelMatrix = glm::translate(finalModelMatrix, glm::vec3(sin((float)glfwGetTime()) / 2, cos((float)glfwGetTime()) / 2, 0));
        finalModelMatrix = glm::rotate(finalModelMatrix, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));
        finalModelMatrix = glm::scale(finalModelMatrix, glm::vec3(.5));
        GLuint location = glGetUniformLocation(mainShader, "uModelMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &finalModelMatrix[0][0]);
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
#include "../include/init.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace DragonGameEngine
{
    GLFWwindow* window = nullptr;

    void error_callback(int error, const char* description)
    {
        std::cerr << "Error " << error << ": " << description << "\n";
    }

    int init(const int width, const int height, const std::string& windowTitle, DGEinitfunc initFunc, DGEmainfunc mainFunc)
    {
        glfwSetErrorCallback(error_callback);
        if (!glfwInit()) return -1;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
        window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);

        if (window == nullptr)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        initFunc();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            mainFunc();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void setWindowTitle(const std::string& newTitle)
    {
        glfwSetWindowTitle(window, newTitle.c_str());
    }
}
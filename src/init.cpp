#include <init.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace DragonGameEngine
{
    GLFWwindow* window = nullptr;
    DGEreshapefunc reshapeFunc = nullptr;

    void error_callback(int error, const char* description)
    {
        std::cerr << "Error " << error << ": " << description << "\n";
    }

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        if (reshapeFunc) reshapeFunc(width, height);
    }

    int init(const int width,
        const int height,
        const std::string& windowTitle,
        const DGEreshapefunc reshapeFunc,
        const DGEinitfunc initFunc,
        const DGEmainfunc mainFunc,
        const DGEexitfunc exitFunc)
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

        // Make the window's context current
        glfwMakeContextCurrent(window);

        DragonGameEngine::reshapeFunc = reshapeFunc;
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        initFunc();

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            mainFunc();

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        exitFunc();
        glfwTerminate();
        return 0;
    }

    void setWindowTitle(const std::string& newTitle)
    {
        glfwSetWindowTitle(window, newTitle.c_str());
    }
}
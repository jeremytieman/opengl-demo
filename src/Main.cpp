#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../include/init.h>
#include <iostream>
#include <string>
#include <sstream>

namespace DGE = DragonGameEngine;

unsigned long frameCount = 0UL;
double startTime = 0.0;
std::string windowTitle = "OpenGL Demo";
int width = 1280;
int height = 960;

void initCallback()
{
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
}

void framesPerSecondCalculator()
{
    if (0.0 == startTime)
    {
        startTime = glfwGetTime();
        return;
    }

    auto curTime = glfwGetTime();
    if ((curTime - startTime) < 0.25) return;
    std::stringstream newTitle(windowTitle);
    newTitle << ": " << frameCount * 4 << " Frames Per Second @ " << width << " x " << height;
    DGE::setWindowTitle(newTitle.str());
    frameCount = 0;
    startTime = curTime;
}

void mainCallback()
{
    ++frameCount;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    framesPerSecondCalculator();
}

int main()
{
    return DGE::init(width, height, windowTitle, initCallback, mainCallback);
}
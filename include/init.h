#pragma once

#include <string>

namespace DragonGameEngine
{
    typedef void (* DGEinitfunc)();
    typedef void (* DGEmainfunc)();

    int init(const int width, const int height, const std::string& windowTitle, DGEinitfunc initFunc, DGEmainfunc mainFunc);
    void setWindowTitle(const std::string& newTitle);
}
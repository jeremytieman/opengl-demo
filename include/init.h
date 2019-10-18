#pragma once

#include <string>

namespace DragonGameEngine
{
    typedef void (* DGEinitfunc)();
    typedef void (* DGEmainfunc)();
    typedef void (* DGEexitfunc)();

    int init(const int width,
     const int height,
     const std::string& windowTitle,
     DGEinitfunc initFunc,
     DGEmainfunc mainFunc,
     DGEexitfunc exitFunc);
    void setWindowTitle(const std::string& newTitle);
}
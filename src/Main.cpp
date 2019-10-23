#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../include/init.h>
#include <../include/util.h>
#include <iostream>
#include <string>
#include <sstream>

namespace DGE = DragonGameEngine;
namespace fs = std::filesystem;

unsigned long frameCount = 0UL;
double startTime = 0.0;
std::string windowTitle = "OpenGL Demo";
//int width = 1280;
//int height = 960;
int width = 600;
int height = 600;
GLuint VertexShaderId;
GLuint FragmentShaderId;
GLuint ProgramId;
GLuint VaoId;
//GLuint VboId;
//GLuint ColorBufferId;
GLuint BufferId;
GLuint IndexBufferId;
fs::path exe;

typedef struct
{
    float XYZW[4];
    float RGBA[4];
} Vertex;

void CreateShaders()
{
    GLenum ErrorCheckValue = glGetError();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const auto VertexShaderPath = exe.parent_path() / "shaders/vertex.glsl";
    auto VertexShader = DragonGameEngine::Util::getFileContents(VertexShaderPath.string());
    auto VertextShaderPtr = VertexShader.c_str();
    glShaderSource(VertexShaderId, 1, &VertextShaderPtr, NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    auto FragmentShaderPath = exe.parent_path() / "shaders/fragment.glsl";
    auto FragmentShader = DragonGameEngine::Util::getFileContents(FragmentShaderPath.string());
    auto FragmentShaderPtr = FragmentShader.c_str();
    glShaderSource(FragmentShaderId, 1, &FragmentShaderPtr, NULL);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);

    ErrorCheckValue = glGetError();

    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Could not create the shaders: " << ErrorCheckValue << " \n";
        exit(-1);
    }
}

/*
void CreateVBO()
{
    /*
    GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
         0.0f,  0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f
    };

    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };
    *

   /*
    GLfloat Vertices[] = {
        -0.8f,  0.8f, 0.0f, 1.0f,
         0.8f,  0.8f, 0.0f, 1.0f,
        -0.8f, -0.8f, 0.0f, 1.0f,

        -0.8f, -0.8f, 0.0f, 1.0f,
         0.8f,  0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f
    };

    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    *

    GLfloat Vertices[] = {
        -0.8f,  0.8f, 0.0f, 1.0f,
         0.8f,  0.8f, 0.0f, 1.0f,
        -0.8f, -0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f
    };

    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    GLenum ErrorCheckValue = glGetError();

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    ErrorCheckValue = glGetError();

    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Could not create a VBO: " << ErrorCheckValue << " \n";
        exit(-1);
    }
}
*/

/*
void CreateVBO()
{
    Vertex Vertices[] =
    {
        { { -0.8f, -0.8f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { {  0.0f,  0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { {  0.8f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };


    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    glGenBuffers(1, &VboId);

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    ErrorCheckValue = glGetError();

    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Could not create a VBO: " << ErrorCheckValue << " \n";
        exit(-1);
    }
}
*/

void CreateVBO()
{
    Vertex Vertices[] =
    {
        { { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
        // Top
        { { -0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.0f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
        { { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        // Bottom
        { { -0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.0f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
        { { 0.0f, -1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        // Left
        { { -0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { -0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
        { { -1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        // Right
        { { 0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
        { { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }
    };
    
    GLubyte Indices[] =
    {
        // Top
        0, 1, 3,
        0, 3, 2,
        3, 1, 4,
        3, 4, 2,
        // Bottom
        0, 5, 7,
        0, 7, 6,
        7, 5, 8,
        7, 8, 6,
        // Left
        0, 9, 11,
        0, 11, 10,
        11, 9, 12,
        11, 12, 10,
        // Right
        0, 13, 15,
        0, 15, 14,
        15, 13, 16,
        15, 16, 14
    };

    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    glGenBuffers(1, &BufferId);

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glBindBuffer(GL_ARRAY_BUFFER, BufferId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void initCallback()
{
    CreateShaders();
    CreateVBO();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, (GLvoid *)0);
    framesPerSecondCalculator();
}

void DestroyShaders()
{
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);

    ErrorCheckValue = glGetError();

    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Could not destroy the shaders: " << ErrorCheckValue << " \n";
        exit(-1);
    }
}

void DestroyVBO()
{
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &BufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &IndexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();

    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Could not destroy the VBO: " << ErrorCheckValue << " \n";
        exit(-1);
    }
}

void exitCallback()
{
    DestroyShaders();
    DestroyVBO();
}

int main(int argc, char** argv)
{
    exe = argv[0];
    return DGE::init(width, height, windowTitle, initCallback, mainCallback, exitCallback);
}
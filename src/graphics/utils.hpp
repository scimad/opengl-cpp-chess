#ifndef __UTILS_HPP
#define __UTILS_HPP

#include "GLFW/glfw3.h"

class Color{
    public:
    float r, g, b, a;
    Color();
    Color(float r, float g, float b, float a=1.0);
};


void processInput(GLFWwindow *window);
void GLunbindShaderVertexIndexBuffer();

#endif // __UTILS_HPP

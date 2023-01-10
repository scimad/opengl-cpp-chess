#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <signal.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);

#define GLCALL(x)\
    GLClearError();\
    x;\
    ASSERT(GLIsErrorFree(#x, __FILE__, __LINE__))

void GLClearError();
bool GLIsErrorFree(const char* function, const char* file, int line);


class Color{
    public:
    float r, g, b, a;
    Color();
    Color(float r, float g, float b, float a=1.0);
};

#endif // __UTILS_HPP

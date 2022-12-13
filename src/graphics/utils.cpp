#include "graphics/renderer.hpp"
#include "graphics/utils.hpp"


Color::Color(){};
Color::Color(float r, float g, float b, float a):r(r),g(g),b(b),a(a){};


void GLunbindShaderVertexIndexBuffer(){
    GLCALL(glBindVertexArray(0));
    GLCALL(glUseProgram(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};

#ifndef __RENDERER
#define __RENDERER

#include <signal.h>

#include "GL/glew.h"

#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Texture;

#define ASSERT(x) if (!(x)) raise(SIGTRAP);

#define GLCALL(x)\
    GLClearError();\
    x;\
    ASSERT(GLIsErrorFree(#x, __FILE__, __LINE__))

void GLClearError();
bool GLIsErrorFree(const char* function, const char* file, int line);

class Renderer{
public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const Texture& texture) const;
    void clear() const;
};

#endif

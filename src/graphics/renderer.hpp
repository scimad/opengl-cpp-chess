#ifndef __RENDERER
#define __RENDERER

#include <signal.h>

#include "GL/glew.h"

#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"

#include "ZR/core.hpp"

#include "glm/glm.hpp"
#include "chess/interfaces/drawable.hpp"

class Texture;
class Shader;
class Drawable;

#define ASSERT(x) if (!(x)) raise(SIGTRAP);

#define GLCALL(x)\
    GLClearError();\
    x;\
    ASSERT(GLIsErrorFree(#x, __FILE__, __LINE__))

void GLClearError();
bool GLIsErrorFree(const char* function, const char* file, int line);

class Renderer{
public:
    Renderer();
    Renderer(Shader& shader):shader(shader){};
    Shader shader;
    void draw(Drawable& drawable, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const;//, Shader& shader) const;
    // void draw(Drawable& drawable, const Shader& shader, const Texture& texture) const;
    void clear() const;
};

#endif

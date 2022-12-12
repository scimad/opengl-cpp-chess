#include <ZR/core.hpp>

#include <GL/glew.h>
#include "renderer.hpp"


void GLClearError(){
    while (glGetError() != GL_NO_ERROR){};
}

bool GLIsErrorFree(const char* function, const char* file, int line){
    bool is_error_free = true;
    while (GLenum error = glGetError()){
        zr::log("OpenGL Error (code "
        + std::to_string(error) +  ") from: " + function + " " + file + ":" + std::to_string(line), zr::VERBOSITY_LEVEL::ERROR);
        is_error_free = false;
    }
    return is_error_free;
}

void Renderer::clear() const{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const Texture& texture) const{
        // clear();
        // Above clear() function gives issue. If we are making multiple draw calls to render multiple stuffs,
        // then, clear() clears the recently drawn object() which will result in that object not appearing on screen at all.
        // So, for now removing tha clear(); function on draw call and calling clear() only once.

        texture.bind();
        shader.bind();
        va.bind();
        ib.bind();
        GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
};

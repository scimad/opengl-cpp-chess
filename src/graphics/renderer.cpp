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
    if (is_error_free == false){
        zr::log("OpenGL found some error!!!!!");
    }
    return is_error_free;
}

Renderer::Renderer(){}

void Renderer::clear() const{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::draw(Drawable& drawable, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj)const {//, Shader& shader) const{
        drawable.bind_va_ib_texture();
        shader.bind();
        GLCALL(glDrawElements(GL_TRIANGLES, drawable.get_ibCount(), GL_UNSIGNED_INT, nullptr));
};

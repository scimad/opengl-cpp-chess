#include <ZR/core.hpp>

#include <GL/glew.h>
#include "renderer.hpp"
#include "graphics/utils.hpp"


Renderer::Renderer(){}

void Renderer::clear() const{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::draw(Drawable& drawable, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj)const {//, Shader& shader) const{
        drawable.bind_va_ib_texture();
        shader.bind();
        GLCALL(glDrawElements(GL_TRIANGLES, drawable.get_ibCount(), GL_UNSIGNED_INT, nullptr));
};

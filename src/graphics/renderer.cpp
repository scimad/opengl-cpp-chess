#include <ZR/core.hpp>

#include <GL/glew.h>
#include "graphics/utils.hpp"
#include "graphics/renderer.hpp"
#include "graphics/model.hpp"


Renderer::Renderer(){}

void Renderer::clear() const{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
};
void Renderer::draw(const DrawableModel& drawable_model) const {
    drawable_model.bind();
    GLCALL(glDrawElements(GL_TRIANGLES, drawable_model.get_ibCount(), GL_UNSIGNED_INT, nullptr));
};

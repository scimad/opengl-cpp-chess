#ifndef __RENDERER
#define __RENDERER

#include "GL/glew.h"

#include "graphics/vertex_array.hpp"
#include "graphics/index_buffer.hpp"
#include "graphics/shader.hpp"
#include "graphics/utils.hpp"
#include "graphics/model.hpp"

#include "ZR/core.hpp"

#include "glm/glm.hpp"

class Texture;
class Shader;

class Renderer{
public:
    Renderer();
    Renderer(Shader& shader):shader(shader){};
    Shader shader;
    void draw(const DrawableModel& drawable_model) const;
    void clear() const;
};

#endif

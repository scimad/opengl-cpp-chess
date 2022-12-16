#ifndef __RENDERER
#define __RENDERER

#include "GL/glew.h"

#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "graphics/utils.hpp"

#include "ZR/core.hpp"

#include "glm/glm.hpp"
#include "chess/interfaces/drawable.hpp"

class Texture;
class Shader;
class Drawable;


class Renderer{
public:
    Renderer();
    Renderer(Shader& shader):shader(shader){};
    Shader shader;
    void draw(Drawable& drawable, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const;//, Shader& shader) const;
    // void draw(Drawable& drawable, const Shader& shader, const Texture& texture) const;
    void clear() const;
    void old_draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const Texture& texture) const{
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
};

#endif

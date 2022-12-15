#ifndef __DRAWABLE_HPP
#define __DRAWABLE_HPP

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/vertex_array.hpp"
#include "graphics/index_buffer.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_buffer_layout.hpp"

#include "glm/glm.hpp"

class Texture;
class Drawable{
private:
    float vertex_data[16];
    unsigned int index_data[6];
    VertexArray va;
    VertexBuffer vb;
    VertexBufferLayout layout;
    IndexBuffer ib;
    Texture texture;

public:
    void bind_va_ib_texture();
    unsigned int get_ibCount() const;
    Drawable();
    ~Drawable();
};


#endif //__DRAWABLE_HPP

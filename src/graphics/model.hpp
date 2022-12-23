#ifndef __MODEL_HPP
#define __MODEL_HPP

#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_array.hpp"
#include "graphics/texture.hpp"
#include "graphics/index_buffer.hpp"
#include "graphics/shader.hpp"

#include <memory>
class DrawableModel
{
private:
    std::unique_ptr<VertexBuffer> vb_ptr;
    std::unique_ptr<VertexBufferLayout> layout_ptr;
    std::unique_ptr<IndexBuffer> ib_ptr;
    std::unique_ptr<Texture> texture_ptr;
    std::unique_ptr<VertexArray> va_ptr;

public:
    std::unique_ptr<Shader> shader_ptr;

    // vertex_data stuff should (?) be heap allocated or maybe use std::vector kinda things 
    float vertex_data[16] = {
     -33.0,  -33.0, 0.0, 0.0,
      33.0,  -33.0, 1.0, 0.0,
      33.0,   33.0, 1.0, 1.0,
     -33.0,   33.0, 0.0, 1.0
    };

    // index_data stuff should (?) be heap allocated or maybe use std::vector kinda things 
    unsigned int index_data[6] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int get_ibCount() const;

    void bind() const;
    DrawableModel(const std::string& shader_path, const std::string& texture_path);
    ~DrawableModel();
};

#endif// __MODEL_HPP
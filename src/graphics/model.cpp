#include "graphics/model.hpp"
#include "graphics/index_buffer.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"

#include <memory>


DrawableModel::DrawableModel(const std::string& shader_path, const std::string& texture_path):
    shader_ptr(std::make_unique<Shader>(shader_path)),texture_ptr(std::make_unique<Texture>(texture_path))
{
    va_ptr = std::make_unique<VertexArray>();

    // 4 vertices, 4 float data per vertices, all models might not have same vb
    vb_ptr = std::make_unique<VertexBuffer>(vertex_data, 4 * 4 * sizeof(float));

    layout_ptr = std::make_unique<VertexBufferLayout>();
    (*layout_ptr).push<float>(2); // for x, y
    (*layout_ptr).push<float>(2); // for texture u, v
    (*va_ptr).addBuffer(*vb_ptr, *layout_ptr);
    ib_ptr = std::make_unique<IndexBuffer>(index_data, 6);
    (*texture_ptr).bind();

    (*shader_ptr).bind();
    (*shader_ptr).setUniform1i("u_texture", 0);

};

DrawableModel::~DrawableModel(){

};

void DrawableModel::bind(){
    (*texture_ptr).bind();
    (*va_ptr).bind();
    (*ib_ptr).bind();
};

unsigned int DrawableModel::get_ibCount() const{
    return (*ib_ptr).getCount();
};

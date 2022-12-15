#include "drawable.hpp"
#include  "graphics/texture.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <ZR/core.hpp>

Drawable::Drawable(/* args */):vb(vertex_data, 4 * 4 * sizeof(float)), texture("../assets/Board.png"), ib(index_data, 6)
{

    float vertex_data[16] = {
     -50.0,  -50.0, 0.0, 0.0,
      50.0,  -50.0, 1.0, 0.0,
      50.0,   50.0, 1.0, 1.0,
     -50.0,   50.0, 0.0, 1.0
    };

    unsigned int index_data[6] = {
        0, 1, 2,
        2, 3, 0
    };
    va.bind();
    // vb = VertexBuffer(vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices 
    layout.push<float>(2); //for x, y
    layout.push<float>(2); //for texture u, v
    va.addBuffer(vb, layout);
    // ib = IndexBuffer(index_data, 6);
    // texture = Texture("../assets/Board.png");                          //https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces
}


void Drawable::bind_va_ib_texture(){
    texture.bind();
    va.bind();
    ib.bind();
}

unsigned int Drawable::get_ibCount() const{
    return ib.getCount();
};

Drawable::~Drawable()
{
}

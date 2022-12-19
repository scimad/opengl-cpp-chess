#include "graphics/model_factory.hpp"
DrawableModel ModelFactory::getQueen(){
    DrawableModel drawable_model;
    // VertexArray va_dqueen;
    // VertexBuffer vb_dqueen(drawable_model.vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices
    // VertexBufferLayout layout_dqueen;
    // layout_dqueen.push<float>(2); //for x, y
    // layout_dqueen.push<float>(2); //for texture u, v
    // va_dqueen.addBuffer(vb_dqueen, layout_dqueen);
    // IndexBuffer ib_dqueen(drawable_model.index_data, 6);
    // Shader shader_dqueen("../res/dark.shader");
    // shader_dqueen.bind();
    // shader_dqueen.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);
    // Texture texture_dqueen("../assets/Chess_qdt45.svg.png"); // ^3
    // texture_dqueen.bind();
    // shader_dqueen.setUniform1i("u_texture", 0);
    /* If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered
    // depending on the program logic*/
    // va_dqueen.unbind();
    // vb_dqueen.unbind();
    // ib_dqueen.unbind();
    // shader_dqueen.unbind();

    return drawable_model;
}

DrawableModel ModelFactory::getRook(){
    DrawableModel drawable_model;
    // VertexArray va_dqueen;
    // VertexBuffer vb_dqueen(drawable_model.vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices
    // VertexBufferLayout layout_dqueen;
    // layout_dqueen.push<float>(2); //for x, y
    // layout_dqueen.push<float>(2); //for texture u, v
    // va_dqueen.addBuffer(vb_dqueen, layout_dqueen);
    // IndexBuffer ib_dqueen(drawable_model.index_data, 6);
    // Shader shader_dqueen("../res/dark.shader");
    // shader_dqueen.bind();
    // shader_dqueen.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);
    // Texture texture_dqueen("../assets/Chess_qdt45.svg.png"); // ^3
    // texture_dqueen.bind();
    // shader_dqueen.setUniform1i("u_texture", 0);
    /* If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered
    // depending on the program logic*/
    // va_dqueen.unbind();
    // vb_dqueen.unbind();
    // ib_dqueen.unbind();
    // shader_dqueen.unbind();

    return drawable_model;
}
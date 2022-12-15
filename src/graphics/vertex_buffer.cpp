#include "vertex_buffer.hpp"

#include "renderer.hpp"

// VertexBuffer::VertexBuffer(){
// 	zr::log("Empty vertex buffer created for now.");
// };

VertexBuffer::VertexBuffer(const void* data, unsigned int size){

    if (data){
        GLCALL(glGenBuffers(1, &rendererID));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
        zr::log("Vertex buffer created!!");
        zr::log("Vertex buffer ID: " + std::to_string(rendererID));
    }

};
VertexBuffer::~VertexBuffer(){
    GLCALL(glDeleteBuffers(1, &rendererID));
};

void VertexBuffer::bind() const{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
};

void VertexBuffer::unbind() const{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
};



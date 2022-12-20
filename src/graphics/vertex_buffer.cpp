#include "ZR/core.hpp"
#include "vertex_buffer.hpp"
#include "graphics/utils.hpp"

#include "GL/glew.h"

VertexBuffer::VertexBuffer(){
	zr::log("Empty vertex buffer created for now.");
};

VertexBuffer::VertexBuffer(const void* data, unsigned int size){

    // if (data){
        GLCALL(glGenBuffers(1, &rendererID));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
        zr::log("VertexBuffer with ID " + std::to_string(rendererID) + " created.");
    // }

};
VertexBuffer::~VertexBuffer(){
    zr::log("VertexBuffer with ID " + std::to_string(rendererID) + " deleted.");
    GLCALL(glDeleteBuffers(1, &rendererID));
};

void VertexBuffer::bind() const{
    zr::log("VertexBuffer with ID " + std::to_string(rendererID) + " binded.");
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
};

void VertexBuffer::unbind() const{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
};



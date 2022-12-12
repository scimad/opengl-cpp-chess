#ifndef __VERTEX_ARRAY
#define __VERTEX_ARRAY

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"


class VertexArray{
private:
    unsigned int rendererID;

public:
    VertexArray();
    ~VertexArray();
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void addLayout(VertexBufferLayout buf_layout);
    void bind() const;
    void unbind() const;
};

#endif //__VERTEX_ARRAY

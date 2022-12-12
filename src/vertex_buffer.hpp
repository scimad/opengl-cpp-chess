#ifndef __VERTEX_BUFFER
#define __VERTEX_BUFFER

class VertexBuffer
{
private:
    unsigned int rendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};




#endif //__VERTEX_BUFFER

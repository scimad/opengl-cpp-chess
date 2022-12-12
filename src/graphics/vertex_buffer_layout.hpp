#ifndef __VERTEX_BUFFER__LAYOUT
#define __VERTEX_BUFFER__LAYOUT

#include <GL/glew.h>

#include<vector>

struct VertexBufferElement
{
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type){
        switch (type){
            // case GL_FLOAT: return 4;
            // case GL_UNSIGNED_INT: return 4;
            // case GL_UNSIGNED_BYTE: return 1;

            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLchar);
        }
        // ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout{
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

public:
    VertexBufferLayout():stride(0){};
    ~VertexBufferLayout(){};

    template<typename T>
    void push(unsigned int count){
        // static_assert(false);
    };

    inline const std::vector<VertexBufferElement> getElements() const {return elements;}
    inline unsigned int getStride() const {return stride;}
};

#endif //__VERTEX_BUFFER__LAYOUT

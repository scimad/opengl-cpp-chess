#include "renderer.hpp"
#include "vertex_buffer.hpp"
#include "vertex_array.hpp"


VertexArray::VertexArray(){
   
    // Abstracting the following commented codes in the actual constructor
    /*
    Generating at least one VAO is compulsory in core profile but a default one is available in compatibility profile
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    */

    GLCALL(glGenVertexArrays(1, &rendererID));
    GLCALL(glBindVertexArray(rendererID));

};
VertexArray::~VertexArray(){
    GLCALL(glDeleteVertexArrays(1, &rendererID));
};
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++){
        const auto element = elements[i];
        // Abstracting the following commented codes in the actual constructor
        /*
        Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0));
        */
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type,
            element.normalized, layout.getStride(), (const void*) offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
    
};
void VertexArray::addLayout(VertexBufferLayout layout){};
void VertexArray::bind()const{
    GLCALL(glBindVertexArray(rendererID));
};
void VertexArray::unbind()const{
    GLCALL(glBindVertexArray(0));
};

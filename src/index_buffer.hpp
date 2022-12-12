#ifndef __INDEX_BUFFER
#define __INDEX_BUFFER

class IndexBuffer
{
private:
    unsigned int rendererID;
    unsigned int count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const{
        return count;
    };
};




#endif //__INDEX_BUFFER

#ifndef __TEXTURE
#define __TEXTURE

#include "renderer.hpp"

class Texture{
private:
	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, BPP; //bits per pixel
public:
	Texture(const std::string& path);
	~Texture();
	void bind(unsigned int slot=0) const;
	void unbind() const;
};



#endif //__TEXTURE
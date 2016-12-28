#pragma once
#include <string>
#include <vector>
#include "TextureCache.h"

namespace Engine {

class FileLoad
{
public:
	FileLoad();
	~FileLoad();
	//returns true if file is loaded
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& vect); //each line is an element of the vector
	static bool readFileToBuffer(std::string filePath, std::string& buffer); //full document is in the buffer
	
	static GLTexture loadPNG(std::string filePath);
	static GLTexture getTexture(std::string texturePath);
private:
	//static TextureCache _textureCache;
};

}
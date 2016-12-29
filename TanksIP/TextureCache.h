#pragma once
#include <map>
#include "OpenGLTexture.h"

namespace Engine{

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string texturePath);
private:
	std::map<std::string, GLTexture> _textureMap; //first is the texture path, second is the texture (image)
};
}

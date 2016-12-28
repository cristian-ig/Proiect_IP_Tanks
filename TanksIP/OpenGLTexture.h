#pragma once
#include <gl/glew.h>
#include <string>
namespace tanks
{
	//a struct that will hold the textures infos
struct GLTexture 
{
	std::string filePath; //filepath
	GLuint id; //index id
	int width; //dimensions
	int height;
};
}
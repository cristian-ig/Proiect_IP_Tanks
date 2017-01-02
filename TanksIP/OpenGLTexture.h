#pragma once
#include <gl/glew.h>
#include <string>
#include<fstream>
#include<vector>

namespace Engine {

	//a struct that will hold the textures infos
	struct GLTexture
	{
		std::string filePath; //filepath
		GLuint id; //index id
		int width; //dimensions
		int height;
	};
	class OpenGLTexture {
	public:
		OpenGLTexture(std::string filePath)
		{
			_texture = loadTexture(filePath);
		}
		OpenGLTexture()
		{

		}
		GLTexture _texture;




	private:
		GLTexture loadTexture(std::string filePath);
		bool readBufferData(std::string filePath, std::vector<unsigned char>& buffer);
	};
}
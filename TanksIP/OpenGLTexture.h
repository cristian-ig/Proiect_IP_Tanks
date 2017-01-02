#pragma once
#include <gl/glew.h>
#include <string>
#include<fstream>
#include<vector>



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
		int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
		GLTexture loadTexture(std::string filePath);
		bool readBufferData(std::string filePath, std::vector<unsigned char>& buffer);
	};

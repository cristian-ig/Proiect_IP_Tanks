#pragma once
#include "Vertex.h"
#include "OpenGLTexture.h"
#include <gl/glew.h>
#include <cstddef>
#include <string>

namespace Engine {

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);
	void build();

private:
	float _x = 0.0f;
	float _y = 0.0f;
	float _width = 0.0f;
	float _height = 0.0f;
	GLuint _vboID = 0;
	GLTexture _texture { };
};

}
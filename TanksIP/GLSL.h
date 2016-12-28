#pragma once
#include <gl/glew.h>
#include <string>

namespace Engine{

class GLSL
{
public:
	GLSL();
	~GLSL();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& uniformName);

	void bind();

	void unbind();

	void clear();

private:
	void compileShader(const char* source, const std::string& name, GLuint id);

	int _numAttributes = 0;
	GLuint _programID = 0;
	GLuint _vertexShaderID = 0;
	GLuint _fragmentShaderID = 0;
};

}
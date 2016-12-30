#pragma once
#include<string>
#include<gl/glew.h>


namespace Engine {

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

		void use();
		void unuse();

		void dispose();
	private:

		int _numAttributes;

		void compileShader(const char* source, const std::string& name, GLuint id);

		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		bool readFileToBuffer(std::string filePath, std::string& buffer);
	};

}
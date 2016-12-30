#include "GLSL.h"
#include<vector>
#include<fstream>
#include<iostream>
namespace tanks {

	GLSL::GLSL() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{
	}


	GLSL::~GLSL() 
	{
	}

	void GLSL::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
		std::string vertSource;
		std::string fragSource;
		try {
			if (!readFileToBuffer(vertexShaderFilePath, vertSource)) {
				throw"shader load err";
			}
			else std::cout << "Succes";
			if (!readFileToBuffer(fragmentShaderFilePath, fragSource)) {
				throw"shader load err";
			}
			else std::cout << "Succes";
		}
		catch (...) { std::cout << "shader load error"; }
		compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
	}
	void GLSL::compileShadersFromSource(const char* vertexSource, const char* fragmentSource) {
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.
		//Get a program object.
		try {
			_programID = glCreateProgram();

			//Create the vertex shader object, and store its ID
			_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			if (_vertexShaderID == 0) {
				throw " vertex shader creation err";
			}

			//Create the fragment shader object, and store its ID
			_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			if (_fragmentShaderID == 0) {
				throw " fragment shader creation err";
			}

			//Compile each shader
			compileShader(vertexSource, "Vertex Shader", _vertexShaderID);
			compileShader(fragmentSource, "Fragment Shader", _fragmentShaderID);
		}
		catch (...) { }
	}

	void GLSL::linkShaders() {

		//Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

	
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}
	//Adds an attribute to our shader. Should be called between compiling and linking.
	void GLSL::addAttribute(const std::string& attributeName) {
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	GLint GLSL::getUniformLocation(const std::string& uniformName) {
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			throw"GL_INVALID_INDEX";
		}
		return location;
	}
	//enable the shader, and all its attributes
	void GLSL::use() {
		glUseProgram(_programID);
		//enable all the attributes we added with addAttribute
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}
	//disable the shader
	void GLSL::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void GLSL::dispose() {
		if (_programID) glDeleteProgram(_programID);
	}
	void GLSL::compileShader(const char* source, const std::string& name, GLuint id) {

		//tell opengl that we want to use fileContents as the contents of the shader file
		glShaderSource(id, 1, &source, nullptr);

		//compile the shader
		glCompileShader(id);

		//check for errors
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Provide the infolog in whatever manor you deem best.
			//Exit with failure.
			glDeleteShader(id); //Don't leak the shader.
			
		}
	}
	  bool GLSL::readFileToBuffer(std::string filePath, std::string& buffer) {
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);

		//Get the file size
		unsigned int fileSize = (unsigned int)file.tellg();
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be present
		fileSize -= (unsigned int)file.tellg();

		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}

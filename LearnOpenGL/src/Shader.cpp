#include "Shader.h"

// constructor
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// first retrieve the vertex/fragment source code from the path in the function parameter
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream verShaderFile;
	std::ifstream fragShaderFile;
	// ifstream objects should be able to throw exceptions
	verShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		verShaderFile.open(vertexPath);
		fragShaderFile.open(fragmentPath);
		std::stringstream verShaderStream, fragShaderStream;
		// read file's buffer contents into streams
		verShaderStream << verShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();
		// close file handlers
		verShaderFile.close();
		fragShaderFile.close();
		// convert string stream into strings
		vertexCode = verShaderStream.str();
		fragmentCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure err) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << err.what() << std::endl;
	}
	// convert c++ strings into c strings
	const char* verShaderCode = vertexCode.c_str();
	const char* fragShaderCode = fragmentCode.c_str();

	// now compile the shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// compiling the vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &verShaderCode, NULL);
	glCompileShader(vertex);
	// log if there are errors when compiling the vertex shader
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
	}

	// compiling the fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragShaderCode, NULL);
	glCompileShader(fragment);
	// log if there are errors when compiling the fragment shader
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:FRAGMENT:COMPILATION_FAILED" << infoLog << std::endl;
	}

	// create and link all the shaders into one shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// log any errors when linking the shader programs
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// after linking all shaders, delete them as they are not needed anymore
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

// get the ID of the shader program
unsigned int Shader::getID() const {
	return ID;
}

// use/activate the shader
void Shader::use() {
	glUseProgram(ID);
}

// utility functions
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


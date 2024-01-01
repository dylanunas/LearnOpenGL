#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

class Shader {
private:
	// the shader program
	unsigned int ID;

public:

	// constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	// destructor
	~Shader() = default;

	// use/activate the shader
	void use();

	// utility functions

	// getters
	
	// get the ID of the shader program
	unsigned int getID() const;

	// setters
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif // SHADER_H
#ifndef INIT_H
#define INIT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window {

	// window size should change when user resizes the screen
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// function declaration for user inputs
	void processInput(GLFWwindow* window);

	// Initializes glfw window
	GLFWwindow* initializeWindow(int width, int height, const char* title, int version);

}

#endif // INIT_H

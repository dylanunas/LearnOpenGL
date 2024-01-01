#include <iostream>

#include "Window.h"

namespace Window {

	// window size should change when user resizes the screen
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		return;
	}

	// if the escape key has been pressed, close the glfw window
	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		return;
	}

	// Initializes glfw window
	GLFWwindow* initializeWindow(int width, int height, const char* title, int version) {
		// glfw configuration, uses OpenGL version 3 and set profile to core
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		// GLFW window initialization
		GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL) {
			std::cout << "ERROR: Failed to create GLFW window!" << std::endl;
			glfwTerminate();
		} 
		else {
			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
		}
		// GLAD initialization and load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
		}
		return window;
	}
}
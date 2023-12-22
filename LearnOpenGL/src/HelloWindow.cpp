#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// window size should change when user resizes the screen
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// function declaration for user inputs
void processInput(GLFWwindow* window);

int main() {
	
	// glfw configuration, uses OpenGL version 3 and set profile to core
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// GLFW window initialization
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "ERROR: Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// GLAD initialization and load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	// viewport
	glViewport(0, 0, 800, 600);
	
	// the application should keep running until we explicitly told it to stop
	while (!glfwWindowShouldClose(window)) {
		// listen to escape key being pressed to close the GLFW window
		processInput(window);
		
		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// listen to events
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// delete all GLFW resources before terminating the program
	glfwTerminate();
	return 0;
}

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
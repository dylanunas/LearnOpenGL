#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// window size should change when user resizes the screen
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// function declaration for user inputs
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main() {\n"
	"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

int main() {
	
	// glfw configuration, uses OpenGL version 3 and set profile to core
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// GLFW window initialization
	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);
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

	// create the vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// bind the GLSL code to the vertex shader then compile the code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check if the vertex shader compile was a success or not.
	// If not check and print out information and see any errors.
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 3D coords for a triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	// bind the newly created buffer to a VBO then copy the vertex data onto the buffer's memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

// include the stb_image.h file
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

#include "Window/Window.h"
#include "ShaderManager/Shader.h"


int main() {
	
	// initialize OpenGL version and the glfw window
	GLFWwindow* window = Window::initializeWindow(1280, 720, "LearnOpenGL", 3);
	if (window == NULL) {
		return -1;
	}
	// link all the shader programs
	Shader shaderProgram(
		"src/ShaderPrograms/vertexShaderSource.vert",
		"src/ShaderPrograms/fragmentShaderSource.frag"
	);

	// 3D coords for a triangle
	float vertices[] = {
		// positions		 // colours         // texture coords
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // bottom left
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,   // top left
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f    // top right
	};
	unsigned int indices[] = {
		0, 1, 2,  // first triangle
		1, 2, 3   // second triangle
	};

	unsigned int EBO, VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the VAO
	glBindVertexArray(VAO);	
	// bind the newly created buffer to a VBO then copy the vertex data onto the buffer's memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coordinates attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ==================== creating and loading a texture =======================
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load the texture from an image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
	// check if the data has loaded successfully
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: Failed to load the texture!" << std::endl;
	}
	stbi_image_free(data);

	// ============================== render loop ================================
	while (!glfwWindowShouldClose(window)) {
		// listen to escape key being pressed to close the GLFW window
		Window::processInput(window);
		
		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ====================== Drawing a Triangle =======================
		
		// use the program before updating the uniform value
		shaderProgram.use();

		// apply the texture
		glBindTexture(GL_TEXTURE_2D, texture);
		// draw the triangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
		// listen to events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// delete all GLFW resources before terminating the program
	glfwTerminate();
	return 0;
}

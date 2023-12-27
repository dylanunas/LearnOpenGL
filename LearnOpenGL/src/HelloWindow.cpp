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
	"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main() {\n"
	"FragColor = ourColor;\n"
	"}\n\0";

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

	// ============================= Vertex Shader ===============================
	// create the vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// bind the GLSL vertex shader code to the vertex shader object then compile it
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

	// ============================= Fragment Shader ===============================
	// create the fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// bind the GLSL fragment shader code to the fragment shader object then compile it
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check if the fragment shader compile was a success or not.
	// If not check and print out information and see any errors.
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

    // ======================== Linking Shaders ===========================
	// create the shader program object
	unsigned int shaderProgram = glCreateProgram();

	// attach all shaders onto the shader program and link them all together
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check if the compilation is successful or not
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// no longer need shader objects once successfully linked to the shader program
	glDeleteShader(fragmentShader);
	// delete the vertex shader as the shader programs no longer need it
	glDeleteShader(vertexShader);

	// 3D coords for a triangle
	float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f, // bottom right
		 0.0f,  0.5f, 0.0f  // top
	};

	unsigned int EBO, VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the VAO
	glBindVertexArray(VAO);	
	// bind the newly created buffer to a VBO then copy the vertex data onto the buffer's memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// the application should keep running until we explicitly told it to stop
	while (!glfwWindowShouldClose(window)) {
		// listen to escape key being pressed to close the GLFW window
		processInput(window);
		
		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ====================== Drawing a Triangle =======================
		// use the program before updating the uniform value
		glUseProgram(shaderProgram);

		// update the uniform value in fragmentShader in this application
		double timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		// draw the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		// listen to events
		glfwSwapBuffers(window);
		glfwPollEvents();
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
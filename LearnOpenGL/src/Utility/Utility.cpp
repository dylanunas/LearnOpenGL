#include <iostream>

#include "Utility.h"

namespace Utility {
	
	void increaseTextureDiff(GLFWwindow* window, float* diff) {

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			if (*diff >= 1.0f) {
				*diff = 1.0f;
				std::cout << "Can not go over 1.0 for mixing textures!" << std::endl;
			}
			else if (*diff < 1.0f) {
				*diff += 0.001f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			if (*diff <= 0.0f) {
				*diff = 0.0f;
				std::cout << "Can not go under 0.0 for mixing textures!" << std::endl;
			}
			else if (*diff > 0.0f) {
				*diff -= 0.001f;
			}
		}
		return;
	}

}
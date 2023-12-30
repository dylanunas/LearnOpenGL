#version 330 core

out vec4 FragColor;
in vec3 ourColor;

// position input from vertex shader 
in vec3 outPos;

void main() {
	FragColor = vec4(outPos, 1.0);
}

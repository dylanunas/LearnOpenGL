#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float textureDiff = 0.2f;

void main() {
	FragColor = mix(texture(ourTexture, vec2(texCoord.x / 2, texCoord.y / 2)), texture(ourTexture2, vec2(texCoord.x, -texCoord.y)), textureDiff);
}

#version 330 core

out vec4 FragColor;

in vec3 texCoords;
uniform float gama;
uniform samplerCube skybox;

void main() {
	FragColor = texture(skybox, texCoords);
}
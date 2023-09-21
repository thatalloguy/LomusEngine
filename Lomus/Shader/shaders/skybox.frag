#version 330 core

out vec4 FragColor;

in vec3 texCoords;

uniform float gamma;
uniform samplerCube skybox;

void main() {
	FragColor = texture(skybox, texCoords);
	FragColor =  vec4(pow(FragColor.xyz, vec3(1.0f / gamma)), 1.0);
}


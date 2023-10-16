#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightProjection;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main() {
	mat4 model = mat4(1.0);
	vec3 crntPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));
	gl_Position = lightProjection * vec4(crntPos, 1.0);
}
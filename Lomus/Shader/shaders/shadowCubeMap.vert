#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main() {
	mat4 mModel = mat4(1.0);
	mModel *= translation * rotation;
	gl_Position = mModel * vec4(aPos, 1.0);
}
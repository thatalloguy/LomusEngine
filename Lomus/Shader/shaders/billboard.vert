#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 camMatrix;

out vec2 texCoords;

void main() {
    texCoords = aTexCoords;

    gl_Position = camMatrix * vec4(vec3(model * vec4(aPos, 1.0)), 1.0);
}
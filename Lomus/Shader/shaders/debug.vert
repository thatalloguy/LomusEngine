#version 330 core

in vec4 aPos;
in uint vertexColor;

// Imports the camera matrix
uniform mat4 camMatrix;

out vec4 vertexColorOut;

void main() {
    vertexColorOut = vec4((vertexColor & 0xFF0000u) >> 16, (vertexColor & 0x00FF00u) >> 8, vertexColor & 0x0000FFu, 0xFF);
    gl_Position = camMatrix * aPos;
}
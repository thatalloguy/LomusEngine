#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 01) in vec3 aNormal;


// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

uniform float thickness;

void main() {
    vec3 crntPos = vec3(model * translation * -rotation * scale * vec4(aPos + aNormal * thickness, 1.0f));
    gl_Position = camMatrix * vec4(crntPos, 1.0);
}
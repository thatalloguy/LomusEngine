#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;

layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 lightProjection;



void main()
{
    vec3 WorldPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = lightProjection * vec4(WorldPos, 1.0);
}
#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;

layout (location = 2) in vec2 aTex;

out vec3 WorldPos;
out vec3 Normal;
out vec2 TexCoords;

//out vec4 fragPosLight;
//out vec3 fragPos;

uniform mat4 camMatrix;
uniform mat3 normalMatrix;
uniform mat4 model;
uniform mat4 lightProjection;




void main()
{
    TexCoords = aTex;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal;

    gl_Position = camMatrix * vec4(WorldPos, 1.0);
}
#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;


void main()
{
    vec3 color = vec3(texture(screenTexture, texCoords));

    FragColor = vec4(color, 1.0f);
}
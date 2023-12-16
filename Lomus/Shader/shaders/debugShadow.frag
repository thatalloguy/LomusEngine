#version 410 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2DArray depthMap;
uniform float near_plane;
uniform float far_plane;
uniform int layer;


void main()
{
    float depthValue = texture(depthMap, vec3(texCoords, layer)).r;

    FragColor = texture(depthMap, vec3(texCoords, layer));//vec4(vec3(depthValue), 1.0); // orthographic
}
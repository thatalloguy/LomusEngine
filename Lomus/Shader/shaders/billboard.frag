#version 330 core


in vec2 texCoords;
uniform sampler2D billBoardTexture;

out vec4 fragColor;


void main() {
    vec4 texCol = texture(billBoardTexture, texCoords).rgba;
    if(texCol.a < 0.1)
            discard;
    fragColor = texCol;
}
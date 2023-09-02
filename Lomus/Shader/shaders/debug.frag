#version 330

uniform bool useGlobalVertexColor;
uniform vec4 globalVertexColor;

in vec4 vertexColorOut;

out vec4 color;

void main() {
	if (useGlobalVertexColor) {
		color = globalVertexColor;
	} else {
		color = vertexColorOut;
	}
	
}
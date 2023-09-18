#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors

layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aTangent;

layout (location = 4) in vec3 aBitangent;
// Texture Coordinates

//layout (location = 5) in vec3 aBitangent;


// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;

out vec4 fragPosLight;
out vec3 fragPos;

out mat3 TBN;


// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 lightProjection;
uniform vec3 camPos;

uniform sampler2D texture_normal0;



void main()
{
	vec3 T = normalize(vec3(model * vec4(aTangent,   0.0)));
	vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(aNormal,    0.0)));
	TBN = mat3(T, B, N);

	//TBN = transpose(TBN);

	fragPos = vec3(model * vec4(aPos, 1.0));
	// calculates current position
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"

	Normal = aNormal;
	// Assigns the colors from the Vertex Data to "color"
	color = vec3(1, 1, 1);//aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;//mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	fragPosLight = lightProjection * vec4(crntPos, 1.0);
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);


}
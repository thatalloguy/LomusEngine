#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 3) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;

layout (location = 5) in vec3 aTangent;
layout (location = 6) in vec3 aBitangent;


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

out vec3 TangentViewPos;
out vec3 TangentFragPos;


// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 lightProjection;
uniform vec3 camPos;

void main()
{
	fragPos = vec3(model * vec4(aPos, 1.0));
	// calculates current position
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"

	Normal = aNormal;
	Normal.z = -Normal.z;
	Normal.x = -Normal.x;
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;//mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	fragPosLight = lightProjection * vec4(crntPos, 1.0);
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);


	// now its time for tangents stuff :/
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * aTangent);
	vec3 N = normalize(normalMatrix * aNormal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	mat3 TBN = transpose(mat3(T, B, N));
	TangentViewPos = TBN * camPos;
	TangentFragPos = TBN * fragPos;

}
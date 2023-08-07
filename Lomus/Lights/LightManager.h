#pragma once
#include "../Shader/ShaderClass.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

using namespace std;

struct Light {
	float lightPosition[3];
	float lightColor_r;
	float lightColor_g;
	float lightColor_b;
	float lightColor_a;
	float lightInten;
};

class LightManager
{
public:
	void Init();
	void Delete();
	void createNewLight(glm::vec3 position, glm::vec4 color, float inten, string id);
	/*
	glm::vec3 getLightPosition(string id);
	glm::vec4 getLightColor(string id);
	float     getLightInten(string id);
	*/
	void setLightPosition(string id, glm::vec3 newPosition);
	void setLightColor(string id,    glm::vec4    newColor);
	void setLightInten(string id,    float        newInten);

	void updateShader(Shader shader);

	void deleteLight(string id);
private:
	unordered_map<string, int> lightIdMap;
	bool castShadow = false;
	Light currentShadowCaster;
	Light lights[100];
	int placeId = 0;
	unsigned int lightBuffer;
};

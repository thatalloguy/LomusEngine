
#include "LightManager.h"

void LightManager::Init()
{

}

void LightManager::Delete()
{

}

void LightManager::createNewLight(glm::vec3 position, glm::vec4 color, float inten, string id)
{
	std::cout << "POSITION: " << position.x << " | " << position.y << " | " << position.z << "\n";
	std::cout << "COLOR: " << color.x << " | " << color.y << " | " << color.z << "\n";
	lightIdMap.emplace(id, placeId);
	
	Light newLight = { {position.x, position.y, position.z}, color.r, color.g, color.b, color.a, inten };
	lights[placeId] = newLight;
	placeId++;
}


void LightManager::updateShader(Shader shader)
{

	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, "numLights"), placeId);
	for (int i = 0; i < placeId; i++) { // placeId is the num of lights
		std::string curP = "lights[" + std::to_string(i) + "].lightPosition";
		std::string curC = "lights[" + std::to_string(i) + "].lightColor";
		std::string curI = "lights[" + std::to_string(i) + "].lightInten";
		Light cLight = lights[i];
		shader.Activate();
		glUniform3f(glGetUniformLocation(shader.ID, curC.c_str()), cLight.lightColor_r, cLight.lightColor_g, cLight.lightColor_b);
		glUniform3f(glGetUniformLocation(shader.ID, curP.c_str()), cLight.lightPosition[0], cLight.lightPosition[1], cLight.lightPosition[2]);
		glUniform1f(glGetUniformLocation(shader.ID, curI.c_str()), cLight.lightInten);
	}
	
}

/*
float LightManager::getLightPosition(string id)
{
	int findId = lightIdMap.at(id);
	return lights[findId].lightPosition;
}

glm::vec4 LightManager::getLightColor(string id)
{
	int findId = lightIdMap.at(id);
	return lights[findId].lightColor;
}

float LightManager::getLightInten(string id)
{
	int findId = lightIdMap.at(id);
	return lights[findId].lightInten;
}
*/

void LightManager::setLightPosition(string id, glm::vec3 newPosition)
{
	int findId = lightIdMap.at(id);
	lights[findId].lightPosition[1] = newPosition.x;
	lights[findId].lightPosition[2] = newPosition.y;
	lights[findId].lightPosition[3] = newPosition.z;
}

void LightManager::setLightColor(string id, glm::vec4 newColor)
{
	int findId = lightIdMap.at(id);
	lights[findId].lightColor_r = newColor.r;
	lights[findId].lightColor_g = newColor.g;
	lights[findId].lightColor_b = newColor.b;
	lights[findId].lightColor_a = newColor.a;
}

void LightManager::setLightInten(string id, float newInten)
{
	int findId = lightIdMap.at(id);
	lights[findId].lightInten = newInten;
}

void LightManager::deleteLight(string id)
{
	lightIdMap.erase(id);
}


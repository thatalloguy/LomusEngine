
#include "LightManager.h"

void LightManager::Init()
{

}

void LightManager::Delete()
{

}


void LightManager::updateShader(Shader& shader, Scene& scene)
{

	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, "numLights"), placeId);
	for (int i = 0; i < placeId; i++) { // placeId is the num of lights
		std::string curP = "lights[" + std::to_string(i) + "].lightPosition";
		std::string curC = "lights[" + std::to_string(i) + "].lightColor";
		std::string curI = "lights[" + std::to_string(i) + "].lightInten";
		std::string curA = "lights[" + std::to_string(i) + "].lightAngle";
		std::string curT = "lights[" + std::to_string(i) + "].lightType";


		Light cLight = lights[i];
		shader.Activate();
		glUniform3f(glGetUniformLocation(shader.ID, curC.c_str()), cLight.lightColor_r, cLight.lightColor_g, cLight.lightColor_b);
		glUniform3f(glGetUniformLocation(shader.ID, curP.c_str()), cLight.lightPosition[0], cLight.lightPosition[1], cLight.lightPosition[2]);
		glUniform1f(glGetUniformLocation(shader.ID, curI.c_str()), cLight.lightInten);
		glUniform3f(glGetUniformLocation(shader.ID, curA.c_str()), cLight.lightAngle[0], cLight.lightAngle[1], cLight.lightAngle[2]);
		glUniform1i(glGetUniformLocation(shader.ID, curT.c_str()), cLight.lightType);
	}
	
}


glm::vec3 LightManager::getLightPosition(Scene& scene, string& id)
{
	int findId = lightIdMap.at(scene.name).at(id);
	return glm::vec3(lights[findId].lightPosition[0], lights[findId].lightPosition[1], lights[findId].lightPosition[2]);
}

glm::vec4 LightManager::getLightColor(Scene& scene, string& id)
{
	int findId = lightIdMap.at(scene.name).at(id);
	return glm::vec4(lights[findId].lightColor_r, lights[findId].lightColor_g, lights[findId].lightColor_b, lights[findId].lightColor_a);
}

float LightManager::getLightInten(Scene& scene, string& id)
{
	int findId = lightIdMap.at(scene.name).at(id);
	return lights[findId].lightInten;
}


void LightManager::setLightPosition(Scene& scene, string id, glm::vec3& newPosition)
{
	int findId = lightIdMap.at(scene.name).at(id);
	lights[findId].lightPosition[1] = newPosition.x;
	lights[findId].lightPosition[2] = newPosition.y;
	lights[findId].lightPosition[3] = newPosition.z;
}

void LightManager::setLightColor(Scene& scene, string& id, glm::vec4& newColor)
{
	int findId = lightIdMap.at(scene.name).at(id);
	lights[findId].lightColor_r = newColor.r;
	lights[findId].lightColor_g = newColor.g;
	lights[findId].lightColor_b = newColor.b;
	lights[findId].lightColor_a = newColor.a;
}

void LightManager::setLightInten(Scene& scene, string& id, float newInten)
{
	int findId = lightIdMap.at(scene.name).at(id);
	lights[findId].lightInten = newInten;
}

void LightManager::deleteLight(Scene& scene, string& id)
{
	lightIdMap.erase(id);
}


void LightManager::InitScene(Scene &scene) {
    unordered_map<string, int> newMap;
    lightIdMap.emplace(scene.name, newMap);
}

void LightManager::createNewLight(Scene &scene, Light &light) {
        lightIdMap.at(scene.name).emplace(light.name, placeId);
        lights[placeId] = light;
        placeId++;
}


#include "LightManager.h"

void LightManager::Init()
{

}

void LightManager::Delete()
{

}


void LightManager::updateShader(Shader& shader, std::shared_ptr<Scene> scene)
{

	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, "numLights"), placeId);
    int i = 0;
	for (auto light : lightIdMap.at(scene->name)) { // placeId is the num of lights
		std::string curP = "lights[" + std::to_string(i) + "].lightPosition";
		std::string curC = "lights[" + std::to_string(i) + "].lightColor";
		std::string curI = "lights[" + std::to_string(i) + "].lightInten";
		std::string curA = "lights[" + std::to_string(i) + "].lightAngle";
		std::string curT = "lights[" + std::to_string(i) + "].lightType";
		std::string curS = "lights[" + std::to_string(i) + "].castShadow";


		auto cLight = light.second;
		shader.Activate();
		glUniform3f(glGetUniformLocation(shader.ID, curC.c_str()), cLight->lightColor_r, cLight->lightColor_g, cLight->lightColor_b);
		glUniform3f(glGetUniformLocation(shader.ID, curP.c_str()), cLight->lightPosition_x, cLight->lightPosition_y, cLight->lightPosition_z);
		glUniform1f(glGetUniformLocation(shader.ID, curI.c_str()), cLight->lightInten);
		glUniform3f(glGetUniformLocation(shader.ID, curA.c_str()), cLight->lightAngle[0], cLight->lightAngle[1], cLight->lightAngle[2]);
		glUniform1i(glGetUniformLocation(shader.ID, curT.c_str()), cLight->lightType);
		glUniform1i(glGetUniformLocation(shader.ID, curS.c_str()), cLight->castShadow);
        i++;

	}
	
}



void LightManager::deleteLight(std::shared_ptr<Scene> scene, string& id)
{
	lightIdMap.at(scene->name).erase(id);
}


void LightManager::InitScene(std::shared_ptr<Scene> scene) {
    unordered_map<string, std::shared_ptr<Light>> newMap;
    lightIdMap.emplace(scene->name, newMap);
}

void LightManager::createNewLight(std::shared_ptr<Scene> scene, Light &light) {
    auto newLight = std::make_shared<Light>(light);
    lightIdMap.at(scene->name).emplace(light.name, newLight);
    placeId++;
}

std::shared_ptr<Light> LightManager::getLight(std::shared_ptr<Scene> scene, std::string name) {
    for (auto i : lightIdMap.at(scene->name)) {
        auto light = i.second;
        if (light->name.c_str() == name.c_str()) {
            return light;
        }
    }
    std::cout << "Could not find light: " << name.c_str() << "\n";
}

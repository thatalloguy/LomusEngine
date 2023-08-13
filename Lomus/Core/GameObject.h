#pragma once
#include "../Renderer/Model.h"
#include <glm/glm.hpp>
#include <string>

using namespace std;

class GameObject
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	

	string name;
	int id;

	
	GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale, string name);
	
	void createModel(const char* path);

	void Draw(Shader& defaultShader, Camera& camera);

	void Delete();
private:
	//Components
	Model model;
};


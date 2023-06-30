#pragma once
#include "../Renderer/Model.h"

class GameObject {

public:
	GameObject(Model& model, Shader shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	void Render(Camera camera); // Only Renders the object
	void Update(Camera camera); // Renders + anything else like physics

	void changeShader(Shader& shader);

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

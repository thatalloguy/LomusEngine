#include "GameObject.h"


GameObject::GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale, string name)
{
	GameObject::position = position;
	GameObject::rotation = rotation;
	GameObject::scale = scale;
	GameObject::name = name;
	GameObject::id = -1;
}


void GameObject::createModel(const char* path)
{
	model.load(path);
}


void GameObject::Draw(Shader& defaultShader, Camera& camera)
{
	model.Draw(defaultShader, camera, GameObject::position, GameObject::rotation, GameObject::scale);
}

void GameObject::Delete()
{
}

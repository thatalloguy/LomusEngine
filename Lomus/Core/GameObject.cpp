#include "GameObject.h"


GameObject::GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale, string name)
{
	GameObject::position = position;
	GameObject::rotation = rotation;
	GameObject::scale = scale;
	GameObject::name = name;
	GameObject::id = -1;
}


void GameObject::createModel(std::string const& path)
{
	model.load(path);
}


void GameObject::Draw(Shader& defaultShader, Camera& camera)
{
	model.Draw(defaultShader, camera, matrix, position, rotation, scale);
}

void GameObject::Delete()
{
}

void GameObject::DeletePhysicsData(PhysicsCommon& common)
{
	

}

void GameObject::createModel(const string &path, map<std::string, std::string> &textures) {
    model.load(path, textures);
}

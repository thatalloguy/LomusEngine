#pragma once
#include "GameObject.h"
#include <vector>
#include <unordered_map>
#include <string>

struct Scene {
	std::string name;
	std::vector<GameObject> gameObjects;
};

class SceneManager
{
public:
	void createNewScene(std::string name);
	void addGameObject(GameObject& gameObject);
	void setCurrentScene(std::string name);
	void deleteScene(std::string name);
	Scene getCurrentScene();

	void renderCurrentScene(Shader& shader, Camera& camera);

	void Delete();

private:
	unordered_map<string, Scene> scenes;
	Scene currentScene;
};


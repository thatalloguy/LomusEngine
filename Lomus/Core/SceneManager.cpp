#include "SceneManager.h"

void SceneManager::createNewScene(std::string name)
{
	Scene newScene;
	newScene.name = name;
	scenes.emplace(name, newScene);
}

void SceneManager::addGameObject(GameObject& gameObject)
{
	currentScene.gameObjects.push_back(gameObject);
}

void SceneManager::setCurrentScene(std::string name)
{
	currentScene = scenes.at(name);
}

void SceneManager::deleteScene(std::string name)
{
	scenes.erase(name);
}

Scene SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::renderCurrentScene(Shader& shader,Camera& camera)
{
	for (int i = 0; i < currentScene.gameObjects.size(); i++) {
		currentScene.gameObjects.at(i).Draw(shader, camera);
	}
}

void SceneManager::Delete()
{
	std::unordered_map<std::string, Scene>::iterator it = scenes.begin();

	while (it != scenes.end()) {
		for (int i = 0; i < it->second.gameObjects.size(); i++) {
			it->second.gameObjects.at(i).Delete();
		}
		it++;
	}

}

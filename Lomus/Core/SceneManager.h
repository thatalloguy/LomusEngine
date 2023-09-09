#pragma once

#include "../Physics/DebugRenderer.h"
#include "GameObject.h"
#include <vector>
#include <unordered_map>
#include <string>

struct Scene {
	std::string name;
	std::unordered_map<int, GameObject> gameObjects;
	PhysicsWorld* world;
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void createNewScene(std::string name);
	void addGameObject(GameObject& gameObject, int id);
	void setCurrentScene(std::string name);
	void deleteScene(std::string name);
	Scene &getCurrentScene();
	GameObject &getGameobject(int id);

	void renderCurrentScene(Shader& shader, Camera& camera);

	void Delete();

	//physics stuff
	void createRigidBody(int GameObjectId, BodyType type);
	void addCollisionBoxShape(int GameObjectId, Vector3& halfExtents, Transform& Offset);
	void UpdatePhysicsWorld(float timeStamp);
	void addCollisionSphereShape(int GameObjectId, float radius, Transform& Offset);
	//void addCollisionCapsuleShape(std::string& GameObjectName, float radius, float height, Transform Offset);

	PhysicsCommon common;
	bool doPhysics = true;

	

private:
	unordered_map<string, Scene> scenes;
	Scene currentScene;
	bool isItFirstScene = true;

};

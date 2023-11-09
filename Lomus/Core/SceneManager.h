#pragma once

#include "../Physics/DebugRenderer.h"
#include "GameObject.h"
#include <vector>
#include <unordered_map>
#include <string>

struct Scene {

    std::string name;
	std::unordered_map<int, std::shared_ptr<GameObject>> gameObjects;
	PhysicsWorld* world;
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void createNewScene(std::string name);
	void addGameObject(GameObject& gameObject);
	void setCurrentScene(std::string name);
	void deleteScene(std::string name);
    std::shared_ptr<Scene> getCurrentScene();
    std::shared_ptr<GameObject> getGameobject(int id);

	void renderCurrentScene(Shader& shader, Lomus::Camera& camera);
    void renderShadowMapScene(Shader& shader, Lomus::Camera& camera);

	void Delete();

	//physics stuff
	void createRigidBody(int GameObjectId, BodyType type);
	void addCollisionBoxShape(int GameObjectId, Vector3& halfExtents, Transform& Offset);
	void UpdatePhysicsWorld(float timeStamp);
	void addCollisionSphereShape(int GameObjectId, float radius, Transform& Offset);
	void addCollisionCapsuleShape(int GameObjectId, float radius, float height, Transform& Offset);

    //Mouse picking stuff

	PhysicsCommon common;
	bool doPhysics = true;

    std::shared_ptr<Scene> currentScene;
	

private:

    //Mouse picking stuff
    //void setupIdFramebuffer();
   // void bindIdFrameBuffer();
   // void unbindIdFrameBuffer();
   // void deleteIdFrameBuffer();

    unsigned int FBO;
    unsigned int FBOTexture;

    int idCounter = 0;
	unordered_map<string, std::shared_ptr<Scene>> scenes;
	bool isItFirstScene = true;
    Quaternion tempQuat;
};

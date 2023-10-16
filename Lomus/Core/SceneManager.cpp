#include "SceneManager.h"

SceneManager::SceneManager() {

}

SceneManager::~SceneManager()
{
	Delete();
}

void SceneManager::createNewScene(std::string name)
{
	Scene newScene;
	newScene.name = name;
	newScene.world = common.createPhysicsWorld();
	scenes.emplace(name, newScene);

}

void SceneManager::addGameObject(GameObject& gameObject, int id)
{
	currentScene.gameObjects.emplace(id, gameObject);
}

void SceneManager::setCurrentScene(std::string name)
{

	currentScene = scenes.at(name);
	isItFirstScene = false;
}

void SceneManager::deleteScene(std::string name)
{
	scenes.erase(name);
}

Scene& SceneManager::getCurrentScene()
{
	return SceneManager::currentScene;
}

GameObject& SceneManager::getGameobject(int id)
{
    try {
        GameObject& go = currentScene.gameObjects.at(id);
        return go;
    } catch(int i) {
        std::cerr << "couldnt find game object: " << id << "\n";
    }




}

void SceneManager::renderCurrentScene(Shader& shader, Lomus::Camera& camera)
{
	for (auto& gameObject : currentScene.gameObjects) {
		gameObject.second.Draw(shader, camera);
	}
}


void SceneManager::Delete()
{
	std::unordered_map<std::string, Scene>::iterator it = scenes.begin();

	while (it != scenes.end()) {
		for (auto& gameObject : it->second.gameObjects) {
			it->second.world->destroyRigidBody(gameObject.second.mRigidBody);
			gameObject.second.Delete();
			gameObject.second.DeletePhysicsData(common);
			common.destroyPhysicsWorld(it->second.world);
		}
		it++;
	}

}



void SceneManager::createRigidBody(int GameObjectId, BodyType type)
{
	GameObject& currentGameObject = SceneManager::getGameobject(GameObjectId);
	currentGameObject.Pvec3.x = currentGameObject.position.x;
	currentGameObject.Pvec3.y = -currentGameObject.position.y;
	currentGameObject.Pvec3.z = currentGameObject.position.z;

	currentGameObject.Pquat.x = currentGameObject.rotation.x;
	currentGameObject.Pquat.y = currentGameObject.rotation.y;
	currentGameObject.Pquat.z = currentGameObject.rotation.z;
	currentGameObject.Pquat.w = currentGameObject.rotation.w;
	currentGameObject.transform = Transform(currentGameObject.Pvec3, currentGameObject.Pquat);
	currentGameObject.mRigidBody = currentScene.world->createRigidBody(currentGameObject.transform);
	currentGameObject.mRigidBody->setType(type);
	currentGameObject.isPhysical = true;
	
}

void SceneManager::addCollisionBoxShape(int GameObjectId, Vector3& halfExtents, Transform& Offset)
{
	GameObject& currentGameObject = SceneManager::getGameobject(GameObjectId);
	Collider* collider = currentGameObject.mRigidBody->addCollider(common.createBoxShape(halfExtents), Offset);
	currentGameObject.colliders.push_back(collider);
}
void SceneManager::addCollisionSphereShape(int GameObjectId, float radius, Transform& Offset) {
    GameObject& currentGameObject = SceneManager::getGameobject(GameObjectId);
    Collider* collider = currentGameObject.mRigidBody->addCollider(common.createSphereShape(radius), Offset);
    currentGameObject.colliders.push_back(collider);
}

void SceneManager::addCollisionCapsuleShape(int GameObjectId, float radius, float height, Transform& Offset) {
    GameObject& currentGameObject = SceneManager::getGameobject(GameObjectId);
    Collider* collider = currentGameObject.mRigidBody->addCollider(common.createCapsuleShape(radius, height), Offset);
    currentGameObject.colliders.push_back(collider);
}

void SceneManager::UpdatePhysicsWorld(float timeStamp)
{
	currentScene.world->update(timeStamp);
	for (auto& gameObject : currentScene.gameObjects) {
		
		if (gameObject.second.isPhysical) {

			gameObject.second.position.x = gameObject.second.mRigidBody->getTransform().getPosition().x;
			gameObject.second.position.y = -gameObject.second.mRigidBody->getTransform().getPosition().y;
			gameObject.second.position.z = gameObject.second.mRigidBody->getTransform().getPosition().z;

            tempQuat.x = gameObject.second.mRigidBody->getTransform().getOrientation().x;
            tempQuat.y = gameObject.second.mRigidBody->getTransform().getOrientation().y;
            tempQuat.z = gameObject.second.mRigidBody->getTransform().getOrientation().z;
            tempQuat.w = gameObject.second.mRigidBody->getTransform().getOrientation().w;

            tempQuat.inverse();

            gameObject.second.rotation.x = tempQuat.x;
            gameObject.second.rotation.y = tempQuat.y;
            gameObject.second.rotation.z = tempQuat.z;
            gameObject.second.rotation.w = tempQuat.w;

		}
	}
}

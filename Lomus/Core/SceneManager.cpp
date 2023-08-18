#include "SceneManager.h"

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
	GameObject& go = currentScene.gameObjects.at(id);
	return go;
}

void SceneManager::renderCurrentScene(Shader& shader, Camera& camera)
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
	currentGameObject.Pvec3.y = currentGameObject.position.y;
	currentGameObject.Pvec3.z = currentGameObject.position.z;

	currentGameObject.Pquat.x = currentGameObject.rotation.x;
	currentGameObject.Pquat.y = currentGameObject.rotation.y;
	currentGameObject.Pquat.z = currentGameObject.rotation.z;
	currentGameObject.Pquat.w = currentGameObject.rotation.w;
	std::cout << "DIDNT BREAK YET5 \n";
	currentGameObject.transform.setPosition(currentGameObject.Pvec3);
	std::cout << "DIDNT BREAK YET3 \n";
	currentGameObject.transform.setOrientation(currentGameObject.Pquat);
	std::cout << "DIDNT BREAK YET6 \n";
	currentGameObject.mRigidBody = getCurrentScene().world->createRigidBody(currentGameObject.transform);
	std::cout << "DIDNT BREAK YET7 \n";
	currentGameObject.mRigidBody->setType(type);
	std::cout << "DIDNT BREAK YET8 \n";
	currentGameObject.isPhysical = true;
	
}

void SceneManager::addCollisionBoxShape(int GameObjectId, Vector3& halfExtents, Transform& Offset)
{
	std::cout << "DIDNT BREAK YET1 \n";
	GameObject& currentGameObject = SceneManager::getGameobject(GameObjectId);
	std::cout << "DIDNT BREAK YET2 \n";
	Collider* collider = currentGameObject.mRigidBody->addCollider(common.createBoxShape(halfExtents), Offset);
	std::cout << "DIDNT BREAK YET \n";
	currentGameObject.colliders.push_back(collider);
	std::cout << "DIDNT BREAK YET \n";
}

void SceneManager::UpdatePhysicsWorld(float timeStamp)
{
	currentScene.world->update(timeStamp);
	for (auto& gameObject : currentScene.gameObjects) {
		
		if (gameObject.second.isPhysical) {
			gameObject.second.position.x = gameObject.second.mRigidBody->getTransform().getPosition().x;
			gameObject.second.position.y = gameObject.second.mRigidBody->getTransform().getPosition().y;
			gameObject.second.position.z = gameObject.second.mRigidBody->getTransform().getPosition().z;
		}
	}
}

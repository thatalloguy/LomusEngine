#pragma once
#include "../Renderer/Model.h"
#include <glm/glm.hpp>
#include <string>
#include <reactphysics3d/reactphysics3d.h>

using namespace std;
using namespace reactphysics3d;

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
	void DeletePhysicsData(PhysicsCommon& common);


	//Physics stuff
	RigidBody* mRigidBody;
	Transform transform = Transform();
	Vector3 Pvec3 = Vector3(1, 1, 1);
	Quaternion Pquat = Quaternion::identity();
	
	//Shapes
	std::vector<Collider*> colliders;
	bool isPhysical = false;

private:
	//Components
	Model model;
};


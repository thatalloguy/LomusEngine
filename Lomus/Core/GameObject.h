#pragma once
#include "../Renderer/Model.h"
#include "glm/detail/type_quat.hpp"
#include "../Renderer/Camera.h"
#include <glm/glm.hpp>
#include <string>
#include <reactphysics3d/reactphysics3d.h>

using namespace std;
using namespace reactphysics3d;

namespace Lomus{
    enum RenderPhase{
        shadow,
        normal,
        id
    };
}

class GameObject
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	

	string name;
	int id = -1;

	
	GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale, string name);
	
	void createModel(std::string const& path);
	void createModel(std::string const& path, std::map<std::string, std::string>& textures);

	void Draw(Shader& defaultShader, Lomus::Camera& camera);

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
    glm::mat4 matrix{1.0f};
	Model model;
};


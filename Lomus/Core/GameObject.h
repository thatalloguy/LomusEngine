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


    struct backUpObject {
        int id;
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
    };

    enum ColliderShapeType {
        Box,
        Sphere,
        Capsule
    };



    struct ColliderInfo {
        ColliderShapeType type;
        reactphysics3d::Collider* collider;
        reactphysics3d::BoxShape* boxShape = nullptr;
        reactphysics3d::SphereShape* sphereShape = nullptr;
        reactphysics3d::CapsuleShape* capsuleShape = nullptr;
        bool hasShape = false;
        Transform offsetTransform;
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
	RigidBody* mRigidBody = nullptr;
	Transform transform = Transform();
	Vector3 Pvec3 = Vector3(1, 1, 1);
	Quaternion Pquat = Quaternion::identity();
	
	//Shapes
	Lomus::ColliderInfo colliderInfo;
	bool isPhysical = false;
    Model model;
    bool castsShadow = true;

private:
	//Components
    glm::mat4 matrix{1.0f};
};


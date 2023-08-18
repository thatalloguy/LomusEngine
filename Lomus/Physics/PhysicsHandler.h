#pragma once
#include <reactPhysics3d/reactphysics3d.h>

using namespace reactphysics3d;



struct Settings{
	float gravity[3] = {0, -9.81, 0};
	bool allowSleeping = true;
};

class PhysicsHandler {
public:
	void Init(Settings settings);
	void Update(float timeStep);
	void CleanUp();


	RigidBody* createRigidBody(Transform &transform);

	PhysicsWorld* world;

private:
	PhysicsCommon physicsCommon;
};
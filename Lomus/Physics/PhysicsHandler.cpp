#include "PhysicsHandler.h"

void PhysicsHandler::Update(float timeStep)
{
	PhysicsHandler::world->update(timeStep);
}

void PhysicsHandler::CleanUp() 
{
	physicsCommon.destroyPhysicsWorld(world);
}

RigidBody* PhysicsHandler::createRigidBody(Transform &transform)
{
	
	return world->createRigidBody(transform);
}


void PhysicsHandler::Init(Settings settings)
{
	world = physicsCommon.createPhysicsWorld();
}

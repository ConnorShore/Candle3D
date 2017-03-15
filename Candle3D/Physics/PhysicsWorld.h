#pragma once

#include "Bullet\btBulletDynamicsCommon.h"
#include "RigidBodyComponent.h"

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void initWorld(float gravity, bool debugDraw = false);
	void addRigidBody(RigidBodyComponent* body);
	void step();
	void cleanUp();

	btDiscreteDynamicsWorld* getWorld() { return _world; }

private:
	btDefaultCollisionConfiguration* _collisionConfig;
	btCollisionDispatcher* _dispatcher;
	btBroadphaseInterface* _overlappingPairCache;
	btSequentialImpulseConstraintSolver* _solver;
	btDiscreteDynamicsWorld* _world;


	btAlignedObjectArray<btCollisionShape*> _collisionShapes;
};
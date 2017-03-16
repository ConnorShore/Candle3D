#pragma once

#include "Bullet\btBulletDynamicsCommon.h"
#include "RigidBodyComponent.h"
#include "BulletDebugDrawer.h"
#include "..\Camera.h"

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void initWorld(float gravity, bool debugDraw = false);
	void addRigidBody(RigidBodyComponent* body);
	void debugDraw(Camera& camera, BulletDebugDrawer& drawer);
	void step();
	void cleanUp();

	bool isDebugDraw() const { return _debugDraw; }
	void setDebugDraw(bool draw) { _debugDraw = draw; }
	void setDebugDrawer(btIDebugDraw* drawer) { _world->setDebugDrawer(drawer); }

	btDiscreteDynamicsWorld* getWorld() { return _world; }

private:
	btDefaultCollisionConfiguration* _collisionConfig;
	btCollisionDispatcher* _dispatcher;
	btBroadphaseInterface* _overlappingPairCache;
	btSequentialImpulseConstraintSolver* _solver;
	btDiscreteDynamicsWorld* _world;


	btAlignedObjectArray<btCollisionShape*> _collisionShapes;

	bool _debugDraw;
};
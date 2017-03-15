#include "PhysicsWorld.h"

#include "BoxColliderComponent.h"
#include "SphereColliderComponent.h"
#include "..\GameObject.h"

PhysicsWorld::PhysicsWorld()
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::initWorld(float gravity, bool debugDraw)
{
	_collisionConfig = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfig);
	_overlappingPairCache = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver;
	_world = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfig);
	_world->setGravity(btVector3(0.0f, -gravity, 0.0f));

	if (debugDraw) _world->debugDrawWorld();
}

void PhysicsWorld::addRigidBody(RigidBodyComponent* body)
{
	ColliderType type = body -> collider->colliderType;
	btCollisionShape* shape = body->collider->shape;

	if (type == ColliderType::BOX) {
		BoxColliderComponent* box = static_cast<BoxColliderComponent*>(body->collider);
		shape = new btBoxShape(btVector3(box->size.x / 2.0f, box->size.y / 2.0f, box->size.z / 2.0f));

	}
	else if (type == ColliderType::SPHERE) {
		SphereColliderComponent* sphere = static_cast<SphereColliderComponent*>(body->collider);
		shape = new btSphereShape(sphere->radius);
	}
	else if (type == ColliderType::CYLINDER) {

	}
	else if (type == ColliderType::CAPSULE) {

	}
	else if (type == ColliderType::CONE) {

	}
	else if (type == ColliderType::NONE) {
		//Do nothing
	}
	else {
		printf("%s is not a valid shape type!", body->collider->colliderType);
	}

	_collisionShapes.push_back(shape);
	btTransform shapeTransform;
	shapeTransform.setIdentity();
	GameObject* obj = body->getParent();
	shapeTransform.setOrigin(btVector3(body->getParent()->transform.position.x, body->getParent()->transform.position.y, body->getParent()->transform.position.z));

	float mass = body->mass;
	bool isDynamic = (mass != 0.0f);
	btVector3 localInertia(0.0f, 0.0f, 0.0f);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	body->body = new btRigidBody(rbInfo);

	body->body->activate();
	_world->addRigidBody(body->body);
}

void PhysicsWorld::step()
{
	//TODO: make stepSimulation parameters into step() arguments
	_world->stepSimulation(1.0f / 60.0f, 6);

	int numObjects = _world->getNumCollisionObjects();
	for (int i = 0; i < numObjects; i++) {
		btCollisionObject* obj = _world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body->isActive()) {
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
			else
			{
				trans = obj->getWorldTransform();
			}
			printf("world pos object %d = %f,%f,%f\n", i, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	}
}

void PhysicsWorld::cleanUp()
{
	for (int i = _world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = _world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		_world->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int i = 0; i < _collisionShapes.size(); i++)
	{
		btCollisionShape* shape = _collisionShapes[i];
		_collisionShapes[i] = 0;
		delete shape;
	}

	//delete dynamics world
	delete _world;

	//delete solver
	delete _solver;

	//delete broadphase
	delete _overlappingPairCache;

	//delete dispatcher
	delete _dispatcher;

	delete _collisionConfig;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	_collisionShapes.clear();
}

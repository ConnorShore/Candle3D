#pragma once

#include "..\Component.h"
#include "..\GameObject.h"
#include "ColliderComponent.h"

#include <Bullet\LinearMath\btVector3.h>
#include <Bullet\btBulletDynamicsCommon.h>
#include <glm\glm.hpp>

class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent(ColliderComponent* colliderComponent) : mass(0.0f)
	{
		this->collider = colliderComponent;
	}

	virtual void update() override
	{
		btTransform trans;
		btTransform bodyTransform = body->getCenterOfMassTransform();
		parent->transform.position = glm::vec3(bodyTransform.getOrigin().getX(), bodyTransform.getOrigin().getY(), bodyTransform.getOrigin().getZ());
		parent->transform.rotation = glm::vec3(bodyTransform.getRotation().getX(), bodyTransform.getRotation().getY(), bodyTransform.getRotation().getZ());
	}

	virtual ComponentType getID() override { return "rigid_body"; }

	btRigidBody* body = nullptr;
	ColliderComponent* collider;
	float mass;
};


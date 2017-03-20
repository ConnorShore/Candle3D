#pragma once

#include "..\Component.h"
#include "..\GameObject.h"
#include "ColliderComponent.h"

#include <Bullet\LinearMath\btVector3.h>
#include <Bullet\btBulletDynamicsCommon.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\type_ptr.hpp>

class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent(ColliderComponent* colliderComponent) : mass(0.0f)
	{
		this->collider = colliderComponent;
	}

	virtual void update() override
	{
		btTransform bodyTransform;
		body->getMotionState()->getWorldTransform(bodyTransform);
		parent->transform.position = glm::vec3(bodyTransform.getOrigin().getX(), bodyTransform.getOrigin().getY(), bodyTransform.getOrigin().getZ());


		glm::quat quaternion = glm::quat(bodyTransform.getRotation().getW(), bodyTransform.getRotation().getX(), bodyTransform.getRotation().getY(), bodyTransform.getRotation().getZ());
		parent->transform.rotation = glm::eulerAngles(quaternion);

	}

	virtual ComponentType getID() override { return "rigid_body"; }

	btRigidBody* body = nullptr;
	ColliderComponent* collider;
	float mass;
};


#pragma once

#include "ColliderComponent.h"

class CapsuleColliderComponent : public ColliderComponent
{
public:
	CapsuleColliderComponent() { colliderType = ColliderType::CAPSULE; radius = 0; height = 0.0f; }
	CapsuleColliderComponent(float radius, float height) { colliderType = ColliderType::CAPSULE; this->radius = radius; this->height = height; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "capsule_collider"; }

	float radius, height;
};
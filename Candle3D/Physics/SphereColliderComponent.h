#pragma once

#include "ColliderComponent.h"

class SphereColliderComponent : public ColliderComponent
{
public:
	SphereColliderComponent() { colliderType = ColliderType::SPHERE; }
	SphereColliderComponent(float radius) { colliderType = ColliderType::SPHERE; this->radius = radius; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "sphere_collider"; }

	float radius;
};
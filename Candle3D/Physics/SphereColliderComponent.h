#pragma once

#include "ColliderComponent.h"

class SphereColliderComponent : public ColliderComponent
{
public:
	SphereColliderComponent() { colliderType = ColliderType::SPHERE; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "sphere_collider"; }

	float radius;
};
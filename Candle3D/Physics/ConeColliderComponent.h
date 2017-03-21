#pragma once

#include "ColliderComponent.h"

class ConeColliderComponent : public ColliderComponent
{
public:
	ConeColliderComponent() { colliderType = ColliderType::CONE; radius = 0; height = 0.0f; }
	ConeColliderComponent(float radius, float height) { colliderType = ColliderType::CONE; this->radius = radius; this->height = height; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "cone_collider"; }

	float radius, height;
};
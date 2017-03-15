#pragma once

#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
	BoxColliderComponent() { colliderType = ColliderType::BOX; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "box_collider"; }

	glm::vec3 size;
};
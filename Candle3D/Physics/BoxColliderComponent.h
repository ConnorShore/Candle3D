#pragma once

#include "ColliderComponent.h"
#include "glm\glm.hpp"

class BoxColliderComponent : public ColliderComponent
{
public:
	BoxColliderComponent() { colliderType = ColliderType::BOX; }
	BoxColliderComponent(glm::vec3& size) { colliderType = ColliderType::BOX; this->size = size; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "box_collider"; }

	glm::vec3 size;
};
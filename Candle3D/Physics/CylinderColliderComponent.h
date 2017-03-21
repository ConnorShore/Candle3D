#pragma once

#include "ColliderComponent.h"
#include "glm\glm.hpp"

class CylinderColliderComponent : public ColliderComponent
{
public:
	CylinderColliderComponent() { colliderType = ColliderType::CYLINDER; }
	CylinderColliderComponent(glm::vec3& halfDims) { colliderType = ColliderType::CYLINDER; this->halfDims = halfDims; }
	virtual void update() override {}
	virtual ComponentType getID() override { return "cylinder_collider"; }

	glm::vec3 halfDims;
};
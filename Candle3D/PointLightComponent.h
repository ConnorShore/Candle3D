#pragma once

#include "LightComponent.h"

#include <glm\glm.hpp>


class PointLightComponent : public LightComponent
{
public:

	PointLightComponent(const glm::vec3& displacement, const glm::vec3& col) { offset = displacement; color = col; }
	PointLightComponent(const glm::vec3& col) { offset = glm::vec3(0.0f);  color = col; }
	PointLightComponent() { color = glm::vec3(1.0f); }

	virtual void update() override 
	{
		//position = parent->transform.position;
	}

	virtual ComponentType getID() override { return "point_light"; };

	//----------------------------//

	glm::vec3 offset;
};
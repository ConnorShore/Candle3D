#pragma once

#include "LightComponent.h"

#include <glm\glm.hpp>

class DirectionLightComponent : public LightComponent
{
public:

	DirectionLightComponent(const glm::vec3& dir, glm::vec3& col)
	{
		direction = dir;
		color = col;
		addTag(std::string("light"));
	}

	DirectionLightComponent(const glm::vec3& dir)
	{
		direction = dir;
		color = glm::vec3(0.0f);
		addTag(std::string("light"));
	}

	DirectionLightComponent() { direction = glm::vec3(0.0f, -1.0f, 0.0f); color = glm::vec3(0.0f); }

	virtual void update() override
	{

	}

	virtual ComponentType getID() override { return "direction_light"; };

	//----------------------------//

	glm::vec3 direction;
};
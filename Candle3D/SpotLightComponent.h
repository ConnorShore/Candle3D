#pragma once

#include "LightComponent.h"

#include <glm\glm.hpp>

class SpotLightComponent : public LightComponent
{
public:

	SpotLightComponent(const glm::vec3& offset, const glm::vec3& dir, const glm::vec3& col, float cut)
	{
		position = offset;
		direction = dir;
		color = col;
		cutOff = cut;
		addTag(std::string("light"));
		//parentComponent = "light";
	}

	SpotLightComponent(const glm::vec3& dir, const glm::vec3& col, float cut)
	{
		position = glm::vec3(0.0f);
		direction = dir;
		color = col;
		cutOff = cut;
		addTag(std::string("light"));
		//parentComponent = "light";
	}

	SpotLightComponent(const glm::vec3& col, float cut)
	{
		position = glm::vec3(0.0f);
		direction = glm::vec3(0.0f);
		color = col;
		cutOff = cut;
		addTag(std::string("light"));
		//parentComponent = "light";
	}

	SpotLightComponent() { color = glm::vec3(1.0f); direction = glm::vec3(0.0f, 0.0f, -1.0f); cutOff = cos(glm::radians(12.5)); }

	virtual void update() override
	{

	}

	virtual ComponentType getID() override { return "spot_light"; };

	//----------------------------//

	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
};
#pragma once

#include "LightComponent.h"

#include <glm\glm.hpp>

class PointLightComponent : public LightComponent
{
public:

	PointLightComponent(const glm::vec3& offset, glm::vec3& col, const glm::vec3& attenuationVals)
	{ 
		position = offset;
		color = col; 
		constant = attenuationVals.x;
		linear = attenuationVals.y;
		quadratic = attenuationVals.z;
		addTag(std::string("light"));
		//parentComponent = "light";
	}

	PointLightComponent(const glm::vec3& col, const glm::vec3& attenuationVals)
	{
		position = glm::vec3(0.0f);
		color = col;
		constant = attenuationVals.x;
		linear = attenuationVals.y;
		quadratic = attenuationVals.z;
		addTag(std::string("light"));
		//parentComponent = "light";
	}

	PointLightComponent() { position = glm::vec3(0.0f);  color = glm::vec3(1.0f); constant = 0.0f; linear = 0.0f; quadratic = 0.0f; }

	virtual void update() override 
	{

	}

	virtual ComponentType getID() override { return "point_light"; };

	//----------------------------//

	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
};
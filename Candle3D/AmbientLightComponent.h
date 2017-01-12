#pragma once

#include "LightComponent.h"

#include <glm\glm.hpp>


class AmbientLightComponent : public LightComponent
{
public:

	AmbientLightComponent(float strength, const glm::vec3& col) : ambientStrength(strength) { color = col; }
	AmbientLightComponent(float strength) : ambientStrength(strength) { color = glm::vec3(1.0f); }
	AmbientLightComponent() {}

	virtual void update() override
	{

	}

	virtual ComponentType getID() override  { return "ambient_light"; };

	//----------------------------//

	float ambientStrength;
};
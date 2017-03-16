#pragma once

#include "Component.h"

#include <glm\glm.hpp>

enum LightType
{
	AMBIENT, POINT, SPOT, DIRECTIONAL
};

class LightComponent : public Component
{
public:

	virtual void update() override
	{

	}

	virtual ComponentType getID() override = 0 { return "light"; };

	//----------------------------//

	glm::vec3 color;
	LightType lightType;
};
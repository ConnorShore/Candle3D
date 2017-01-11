#pragma once

#include "Component.h"

class TestComponent : public Component
{
public:
	virtual void update() override
	{
		//printf("Test component update\n");
	}

	virtual ComponentType getID() override { return "test"; }

private:

};
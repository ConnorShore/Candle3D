#pragma once

#include "Component.h"
#include "ShaderProgram.h"

class StaticRenderComponent : public Component
{
public:
	StaticRenderComponent() { }
	~StaticRenderComponent() { }

	virtual void update() override {};

	virtual void render(StaticShader& shader) = 0;

	virtual std::string getID() = 0
	{
		return "renderable";
	};
};
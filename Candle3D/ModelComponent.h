#pragma once

#include "StaticRenderComponent.h"
#include "Model.h"

#include <glm/glm.hpp>

class ModelComponent : public StaticRenderComponent
{
public:
	ModelComponent(const std::string& path)
	{
		_model.init(path);
	}

	~ModelComponent() { }

	virtual void update() override
	{
		
	}

	virtual void render(StaticShader& shader) override
	{ 
		_model.render(shader);
	}

	virtual std::string getID() override { return "model"; }

	glm::vec3 getAABBDimensions() const { return _model.getAABBDimensions() * parent->transform.scale; }

	float specularValue = 0.0f;

private:
	Model _model;
};


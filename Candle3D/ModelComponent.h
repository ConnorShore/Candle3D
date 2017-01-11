#pragma once

#include "StaticRenderComponent.h"
#include "Model.h"

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

private:
	Model _model;
};


#pragma once

#include "StaticShader.h"
#include "Model.h"

#include <vector>

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void init();

	void render(Model& model);

private:
	StaticShader _staticShader;
};


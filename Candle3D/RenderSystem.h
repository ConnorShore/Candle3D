#pragma once

#include "StaticShader.h"
#include "Camera.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void init();
	void prepare();
	void render(Camera& camera);

private:
	StaticShader _staticShader;

	void renderModels();
};


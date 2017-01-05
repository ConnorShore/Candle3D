#pragma once

#include "ShaderProgram.h"

#include <string>
#include <vector>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadTexture();
	void loadCameraMatricies(glm::mat4& view, glm::mat4& projection);
	void loadModelMatrix(glm::mat4& model);

private:
	GLuint _textureLoc, _modelMatrixLoc, _viewMatrixLoc, _projectionMatrixLoc;
};
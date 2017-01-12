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

	void loadCameraMatricies(glm::mat4& view, glm::mat4& projection);
	void loadModelMatrix(glm::mat4& model);
	void loadLights();
	void loadSpecularValue(float value);

private:
	GLuint  _modelMatrixLoc, _viewMatrixLoc, _projectionMatrixLoc, _cameraPosLoc;
	GLuint _lightColorLoc, _ambientStrengthLoc, _lightPositionLoc, _specularValueLoc;
};
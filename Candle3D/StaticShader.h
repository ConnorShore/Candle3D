#pragma once

#include "ShaderProgram.h"

#include <string>
#include <vector>

#define MAX_POINT_LIGHTS 4

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
	void loadAmbient(float ambient);
	void loadViewPos(glm::vec3& position);

private:
	GLuint  _modelMatrixLoc, _viewMatrixLoc, _projectionMatrixLoc, _cameraPosLoc;

	GLuint _specularValueLoc;

	GLuint _ambientStrengthLoc;
	GLuint _viewPosLoc;
	GLuint _dirLightDirLoc, _dirLightColLoc;
	GLuint _pointPosLoc[MAX_POINT_LIGHTS], _pointConstLoc[MAX_POINT_LIGHTS], _pointLinearLoc[MAX_POINT_LIGHTS], _pointQuadLoc[MAX_POINT_LIGHTS], _pointColorLoc[MAX_POINT_LIGHTS];
	GLuint _spotPosLoc, _spotDirLoc, _spotCutoffDir, _spotOuterCutoff, _spotColorLoc;
};
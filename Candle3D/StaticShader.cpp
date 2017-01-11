#include "StaticShader.h"



StaticShader::StaticShader()
{
	
}


StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexNormal");
	bindAttribute(1, "vertexUV");
}

void StaticShader::getUniformLocations()
{
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
}

void StaticShader::loadCameraMatricies(glm::mat4 & view, glm::mat4 & projection)
{
	loadMatrix4f(_viewMatrixLoc, view);
	loadMatrix4f(_projectionMatrixLoc, projection);
}

void StaticShader::loadModelMatrix(glm::mat4& model)
{
	loadMatrix4f(_modelMatrixLoc, model);
}
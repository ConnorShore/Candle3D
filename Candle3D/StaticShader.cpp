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
	//bindAttribute(1, "vertexColor");
	bindAttribute(1, "vertexUV");
}

void StaticShader::getUniformLocations()
{
	_textureLoc = getUniformLocation("mySample");
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");
}

void StaticShader::loadTexture()
{
	loadInt(_textureLoc, 0);
}

void StaticShader::loadViewMatrix(glm::mat4& view)
{
	loadMatrix4f(_viewMatrixLoc, view);
}

void StaticShader::loadProjectionMatrix(glm::mat4 & projection)
{
	loadMatrix4f(_projectionMatrixLoc, projection);
}

void StaticShader::loadModelMatrix(glm::mat4& model)
{
	loadMatrix4f(_modelMatrixLoc, model);
}
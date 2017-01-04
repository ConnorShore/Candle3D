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
	bindAttribute(1, "vertexColor");
	bindAttribute(2, "vertexUV");
}

void StaticShader::getUniformLocations()
{
	_textureLoc = getUniformLocation("mySample");
}

void StaticShader::loadTexture()
{
	loadInt(_textureLoc, 0);
}

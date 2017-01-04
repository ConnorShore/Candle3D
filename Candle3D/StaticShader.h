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

private:

};
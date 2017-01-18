#include "StaticShader.h"
#include "GameObjectManager.h"
#include "Componenets.h"

#include <iostream>

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
	_cameraPosLoc = getUniformLocation("cameraPos");
	_modelMatrixLoc = getUniformLocation("model");
	_viewMatrixLoc = getUniformLocation("view");
	_projectionMatrixLoc = getUniformLocation("projection");

	_specularValueLoc = getUniformLocation("specularValue");

	_ambientStrengthLoc = getUniformLocation("ambient");

	_dirLightDirLoc = getUniformLocation("directionLight.direction");
	_dirLightColLoc = getUniformLocation("directionLight.color");

	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
		auto is = std::to_string(i);
		_pointPosLoc[i] = getUniformLocation("pointLights[" + is + "].position");
		_pointConstLoc[i] = getUniformLocation("pointLights[" + is + "].constant");
		_pointLinearLoc[i] = getUniformLocation("pointLights[" + is + "].linear");
		_pointQuadLoc[i] = getUniformLocation("pointLights[" + is + "].quadratic");
		_pointColorLoc[i] = getUniformLocation("pointLights[" + is + "].color");
	}

	_spotPosLoc = getUniformLocation("spotLight.position");
	_spotDirLoc = getUniformLocation("spotLight.direction");
	_spotCutoffDir = getUniformLocation("spotLight.cutOff");
	_spotOuterCutoff = getUniformLocation("spotLight.outerCutOff");
	_spotColorLoc = getUniformLocation("spotLight.color");
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

void StaticShader::loadLights()
{
	std::vector<GameObject*> gos = GameObjectManager::instance().queryGameObjectsByTag(std::string("light"));
	int numGos = gos.size();

	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
		if (i < numGos) {
			if (gos[i]->hasComponent("point_light")) {
				PointLightComponent* point = static_cast<PointLightComponent*>(gos[i]->getComponent("point_light"));
				loadVector3f(_pointPosLoc[i], gos[i]->transform.position + point->position);
				loadVector3f(_pointColorLoc[i], point->color);
				loadFloat(_pointConstLoc[i], point->constant);
				loadFloat(_pointLinearLoc[i], point->linear);
				loadFloat(_pointQuadLoc[i], point->quadratic);
			}
		}
		else {
			loadVector3f(_pointPosLoc[i], glm::vec3(0.0f));
			loadVector3f(_pointColorLoc[i], glm::vec3(0.0f));
			loadFloat(_pointConstLoc[i], 1.0f);
			loadFloat(_pointLinearLoc[i], 0.0f);
			loadFloat(_pointQuadLoc[i], 0.0f);
		}
	}
}

void StaticShader::loadSpecularValue(float value)
{
	loadFloat(_specularValueLoc, value);
}

void StaticShader::loadAmbient(float ambient)
{
	loadFloat(_ambientStrengthLoc, ambient);
}

void StaticShader::loadViewPos(glm::vec3 & position)
{
	loadVector3f(_viewPosLoc, position);
}

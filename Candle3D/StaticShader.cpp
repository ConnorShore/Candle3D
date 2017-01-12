#include "StaticShader.h"
#include "GameObjectManager.h"
#include "AmbientLightComponent.h"
#include "PointLightComponent.h"
#include "ModelComponent.h"


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

	_ambientStrengthLoc = getUniformLocation("ambientStrength");
	_specularValueLoc = getUniformLocation("specularValue");
	_lightColorLoc = getUniformLocation("lightColor");
	_lightPositionLoc = getUniformLocation("lightPosition");
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
	std::vector<GameObject*> gos = GameObjectManager::instance().getGameObjects();
	int numGos = GameObjectManager::instance().getNumGameObjects();

	for (int i = 0; i < numGos; i++) {
		if (gos[i]->hasComponent("ambient_light")) {
			AmbientLightComponent* ambient = static_cast<AmbientLightComponent*>(gos[i]->getComponent("ambient_light"));
			loadFloat(_ambientStrengthLoc, ambient->ambientStrength);
			loadVector3f(_lightColorLoc, ambient->color);
		}
		if (gos[i]->hasComponent("point_light")) {
			PointLightComponent* point = static_cast<PointLightComponent*>(gos[i]->getComponent("point_light"));
			loadVector3f(_lightColorLoc, point->color);
			loadVector3f(_lightPositionLoc, gos[i]->transform.position + point->offset);
		}
	}
}

void StaticShader::loadSpecularValue(float value)
{
	loadFloat(_specularValueLoc, value);
}

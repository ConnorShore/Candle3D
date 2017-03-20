#include "RenderSystem.h"

#include "Model.h"
#include "Components.h"
#include "GameObjectManager.h"
#include "glm\gtc\matrix_transform.hpp"

RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();;
}

void RenderSystem::prepare()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::render(Camera& camera)
{
	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadCameraMatricies(camera.viewing.viewMatrix, camera.viewing.projectionMatrix);
	_staticShader.loadViewPos(camera.transform.position);
	_staticShader.loadAmbient(0.05f);
	_staticShader.loadLights();

	renderModels();

	_staticShader.stop();
}

void RenderSystem::renderModels()
{
	unsigned int numObjects = GameObjectManager::instance().getNumGameObjects();
	std::vector<GameObject*> objects = GameObjectManager::instance().getGameObjects();

	for (int i = 0; i < numObjects; i++) {
		if (objects[i]->hasComponent("model")) {
			ModelComponent* comp = static_cast<ModelComponent*>(objects[i]->getComponent("model"));
			_staticShader.loadSpecularValue(comp->specularValue);

			glm::mat4 model;

			if (objects[i]->hasComponent("rigid_body")) {
				RigidBodyComponent* body = static_cast<RigidBodyComponent*>(objects[i]->getComponent("rigid_body"));
				btScalar mat[16];
				btTransform trans = body->body->getWorldTransform();
				trans.getOpenGLMatrix(mat);
				model = glm::make_mat4(mat);
				model = glm::scale(model, objects[i]->transform.scale);
			}
			else {
				model = glm::translate(model, objects[i]->transform.position);
				model = glm::rotate(model, objects[i]->transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, objects[i]->transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, objects[i]->transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, objects[i]->transform.scale);
			}

			_staticShader.loadModelMatrix(model);

			comp->render(_staticShader);
		}
	}
}

#include "MainGame.h"
#include "ResourceManager.h"
#include "Components.h"

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

#include "glm\gtc\matrix_transform.hpp"


MainGame::MainGame() : _isRunning(true), _screenWidth(1600), _screenHeight(900)
{
}

MainGame::~MainGame()
{
}

void MainGame::init()
{
	_window.createWindow("Engine Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight);
	_window.setBackgroundColor(glm::vec4(30, 10, 80, 255));

	_renderSystem.init();

	_camera.init(_window, _screenWidth, _screenHeight);
	_physicsWorld.initWorld(10.0f, true);
	_physicsWorld.setDebugDrawer(&_debugDrawer);

	ModelComponent* boxModel = new ModelComponent("Models/unitbox.obj");

	GameObject* unitBox = GameObjectManager::instance().newGameObjectBlueprint();
	unitBox->transform.position = glm::vec3(-2.0f, 5.0f, -20.0f);
	unitBox->transform.rotation = glm::vec3(45.0f, 45.0f, 0.0f);
	unitBox->transform.scale = glm::vec3(2.0f);
	unitBox->attachComponent(boxModel);

	BoxColliderComponent* unitBoxCollider = new BoxColliderComponent();
	unitBoxCollider->size = boxModel->getAABBDimensions();

	RigidBodyComponent* unitBoxBody = new RigidBodyComponent(unitBoxCollider);
	unitBoxBody->mass = 1.0f;

	unitBox->attachComponent(unitBoxBody);
	_physicsWorld.addRigidBody(unitBoxBody);

	GameObject* pointLight = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight->transform.position = _camera.transform.position;
	pointLight->attachComponent(new PointLightComponent(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.045f, 0.0075)));
	
	GameObject* pointLight2 = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight2->transform.position = glm::vec3(0.0f, 1.5f, -30.0f);
	pointLight2->attachComponent(new PointLightComponent(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.045f, 0.0075)));
	pointLight2->attachComponent(new RigidBodyComponent(new SphereColliderComponent(1.0f), 0.0f));
	_physicsWorld.addRigidBody(static_cast<RigidBodyComponent*>(pointLight2->getComponent("rigid_body")));

	GameObject* pointLight3 = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight3->transform.position = glm::vec3(13.0f, 2.5f, -20.0f);
	pointLight3->attachComponent(new PointLightComponent(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.045f, 0.0075f)));

	GameObject* pointLight4 = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight4->transform.position = glm::vec3(-13.0f, 2.5f, -20.0f);
	pointLight4->attachComponent(new PointLightComponent(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.045f, 0.0075f)));

	BoxColliderComponent* groundCollider = new BoxColliderComponent();
	groundCollider->size = glm::vec3(150.0f, 5.0f, 150.0f);

	RigidBodyComponent* groundBody = new RigidBodyComponent(groundCollider);

	GameObject* ground = GameObjectManager::instance().newGameObjectBlueprint();
	ground->transform.position = glm::vec3(-50.0f, -10.0f, -55.0f);
	ground->attachComponent(groundBody);
	_physicsWorld.addRigidBody(groundBody);
}

void MainGame::input()
{
	if (_inputManager.isKeyDown(SDLK_w)) {
		_camera.translate(Translate::FORWARD, 7.0f * _timer.getDeltaTime());
	}
	else if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.translate(Translate::BACK, 7.0f * _timer.getDeltaTime());
	}
	if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.translate(Translate::LEFT, 7.0f * _timer.getDeltaTime());
	}
	else if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.translate(Translate::RIGHT, 7.0f * _timer.getDeltaTime());
	}

	if (_inputManager.isKeyDown(SDLK_F1)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (_inputManager.isKeyDown(SDLK_F2)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (_inputManager.isKeyDown(SDLK_TAB)) {
		_physicsWorld.setDebugDraw(!_physicsWorld.isDebugDraw());
		_inputManager.keyReleased(SDLK_TAB);
	}

	if (_inputManager.isKeyDown(SDLK_SPACE)) {
		RigidBodyComponent* test = static_cast<RigidBodyComponent*>(GameObjectManager::instance().getGameObject(0)->getComponent("rigid_body"));
		test->body->applyCentralForce(btVector3(0, 100, 0));
	}

	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		_camera.setMouseLook(true);
	}
	else {
		_camera.setMouseLook(false);
	}

	//-------------------------//

	if (_inputManager.isKeyDown(SDLK_ESCAPE)) {
		cleanUp();
	}
}

void MainGame::update()
{

	_inputManager.update();
	_camera.update(_inputManager);

	GameObjectManager::instance().updateGameObjects();

	_physicsWorld.step(1.0f/60.0f, 6);
}

void MainGame::render()
{
	_renderSystem.prepare();

	_renderSystem.render(_camera);

	_physicsWorld.debugDraw(_camera, _debugDrawer);

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	_timer.TimeInit();

	while (_isRunning) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		update();
		input();
		render();

		_timer.LimitFPS(60.0f);
		_timer.CalculateFPS(false);
	}
}

void MainGame::cleanUp()
{
	_staticShader.cleanUp();
	_physicsWorld.cleanUp();

	SDL_Quit();
	exit(0);
}

void MainGame::run()
{
	init();
	gameLoop();
	cleanUp();
}
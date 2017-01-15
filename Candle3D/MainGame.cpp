#include "MainGame.h"
#include "ResourceManager.h"
#include "ModelComponent.h"
#include "TestComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

#include "glm\gtc\matrix_transform.hpp"


MainGame::MainGame() : _isRunning(true), _screenWidth(1280), _screenHeight(720)
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

	ModelComponent* spiderModel = new ModelComponent("Models/Spider/spider.obj");
	spiderModel->specularValue = 1.0f;

	GameObject* spider = GameObjectManager::instance().newGameObjectBlueprint();
	spider->transform.position = (glm::vec3(-10.0f, -1.75f, -3.0f));
	spider->transform.scale = glm::vec3(0.15f);
	spider->attachComponent(spiderModel);

	GameObject* spider2 = GameObjectManager::instance().newGameObjectBlueprint();
	spider2->transform.position = (glm::vec3(15.0f, -2.25f, -35.0f));
	spider2->transform.scale = glm::vec3(0.15f);
	spider2->attachComponent(new ModelComponent("Models/Spider/spider.obj"));
	spider2->attachComponent(new PointLightComponent(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(glm::vec3(1.0f, 0.045f, 0.0075))));

	GameObject* pointLight = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight->transform.position = _camera.transform.position;
	pointLight->attachComponent(new PointLightComponent(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.045f, 0.0075)));

	GameObject* pointLight2 = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight2->transform.position = glm::vec3(0.0f, 1.5f, -30.0f);
	pointLight2->attachComponent(new PointLightComponent(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.045f, 0.0075)));

	GameObject* pointLight3 = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight3->transform.position = glm::vec3(10.0f, 2.5f, -20.0f);
	pointLight3->attachComponent(new PointLightComponent(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.045f, 0.0075f)));

	GameObject* pointLight4 = GameObjectManager::instance().newGameObjectBlueprint();
	pointLight4->transform.position = glm::vec3(-10.0f, 2.5f, -20.0f);
	pointLight4->attachComponent(new PointLightComponent(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.045f, 0.0075f)));

	GameObjectManager::instance().getGameObject(0)->transform.position = glm::vec3(-15.0f, -2.25f, -35.0f);
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

	if (_inputManager.isKeyDown(SDL_BUTTON_MIDDLE)) {
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

	GameObjectManager::instance().getGameObject(1)->transform.position += glm::vec3(0.0f, 0.0f, 0.1f);
	GameObjectManager::instance().getGameObject(2)->transform.position = _camera.transform.position;

	GameObjectManager::instance().updateGameObjects();
}

void MainGame::render()
{
	_renderSystem.prepare();

	_renderSystem.render(_camera);

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

	SDL_Quit();
	exit(0);
}

void MainGame::run()
{
	init();
	gameLoop();
	cleanUp();
}
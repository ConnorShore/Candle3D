#include "MainGame.h"
#include "ResourceManager.h"

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "glm\gtc\matrix_transform.hpp"


GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

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

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();

	_camera.init(_window, _screenWidth, _screenHeight);

	_renderSystem.init();

	Model model("Models/Spider/spider.obj");
	_models.push_back(model);
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
}

void MainGame::render()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadTexture();
	_staticShader.loadCameraMatricies(_camera.viewing.viewMatrix, _camera.viewing.projectionMatrix);

	for (Model m : _models) {
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, -3.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.1f));	// It's a bit too big for our scene, so scale it down
		_staticShader.loadModelMatrix(model);
		m.render(_staticShader);
		//_renderSystem.render(m);
	}

	_staticShader.stop();

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

		_timer.LimitFPS(120.0f);
		_timer.CalculateFPS(true);
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
#include "MainGame.h"

#include <SDL\SDL.h>
#include <GL\glew.h>

MainGame::MainGame() : _isRunning(true), _screenWidth(1280), _screenHeight(720)
{

}

MainGame::~MainGame()
{

}

void MainGame::init()
{
	_window.createWindow("Engine Tester", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight);
	_window.setBackgroundColor(glm::vec4(30, 10, 80, 255));
}

void MainGame::input()
{

}

void MainGame::update()
{
	_inputManager.update();
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	SDL_Quit();
	exit(0);
}

void MainGame::run()
{
	init();
	gameLoop();
	cleanUp();
}
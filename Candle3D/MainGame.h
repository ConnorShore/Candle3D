#pragma once

#include "Window.h"
#include "Time.h"
#include "InputManager.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	bool _isRunning;
	int _screenWidth, _screenHeight;

	Window _window;
	Time _timer;
	InputManager _inputManager;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};


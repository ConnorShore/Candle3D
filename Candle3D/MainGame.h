#pragma once

#include "Window.h"
#include "Time.h"
#include "InputManager.h"
#include "StaticShader.h"

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
	StaticShader _staticShader;


	GLuint _vaoID, _vboID, _eboID;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};


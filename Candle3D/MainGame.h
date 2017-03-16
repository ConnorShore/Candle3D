#pragma once

#include "GameObjectManager.h"
#include "Window.h"
#include "Time.h"
#include "InputManager.h"
#include "StaticShader.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"
#include "RenderSystem.h"
#include "Physics\PhysicsWorld.h"
#include "Physics\BulletDebugDrawer.h"

#include <vector>

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
	Camera _camera;
	RenderSystem _renderSystem;
	PhysicsWorld _physicsWorld;
	BulletDebugDrawer _debugDrawer;

	std::vector<Model> _models;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};


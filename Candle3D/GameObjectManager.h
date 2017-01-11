#pragma once

#include "GameObject.h"

#include <vector>

class GameObjectManager
{
public:

	static GameObjectManager& instance()
	{
		static GameObjectManager* sceneManager = new GameObjectManager();
		return *sceneManager;
	}

	GameObject* newGameObjectBlueprint();

	std::vector<GameObject*> getGameObjects() const { return _gameObjects; }
	unsigned int getNumGameObjects() const { return _objectCount; }

	GameObject* getGameObject(unsigned int id)
	{
		return _gameObjects[id];
	}

	void updateGameObjects();

private:
	std::vector<GameObject*> _gameObjects;
	unsigned int _objectCount = 0;

	GameObjectManager();
	~GameObjectManager();
};


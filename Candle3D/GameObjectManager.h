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
	GameObject* newGameObjectBlueprint(unsigned int goID);
	void updateGameObjects();

	std::vector<GameObject*> getGameObjects() const { return _gameObjects; }
	unsigned int getNumGameObjects() const { return _objectCount; }

	std::vector<GameObject*> queryGameObjectsByTag(std::string& tag);

	GameObject* getGameObject(unsigned int id) { return _gameObjects[id]; }


private:
	std::vector<GameObject*> _gameObjects;
	unsigned int _objectCount = 0;

	GameObjectManager();
	~GameObjectManager();
};


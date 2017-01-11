#include "GameObjectManager.h"



void GameObjectManager::updateGameObjects()
{
	for (GameObject* go : _gameObjects) {
		go->update();
	}
}

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

GameObject * GameObjectManager::newGameObjectBlueprint()
{
	GameObject* obj = new GameObject(_objectCount++);
	_gameObjects.push_back(obj);
	return obj;
}

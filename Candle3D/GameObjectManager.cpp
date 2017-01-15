#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	for (int i = _gameObjects.size(); i >= 0; i--) {
		GameObject* go = _gameObjects[i];
		_gameObjects.pop_back();
		delete go;
	}
}

void GameObjectManager::updateGameObjects()
{
	for (GameObject* go : _gameObjects) {
		go->update();
	}
}

std::vector<GameObject*> GameObjectManager::queryGameObjectsByTag(std::string & tag)
{
	std::vector<GameObject*> gos;
	for (GameObject* go : _gameObjects) {
		if (go->hasComponentWithTag(tag))
			gos.push_back(go);
	}
	return gos;
}

//unsigned int GameObjectManager::getNumGameObjects(ComponentType compType)
//{
//	unsigned int count;
//	for (GameObject* go : _gameObjects) {
//		if (go->hasComponent(compType))
//			count++;
//
//	}
//
//	return count;
//}

GameObject* GameObjectManager::newGameObjectBlueprint()
{
	GameObject* obj = new GameObject(_objectCount++);
	_gameObjects.push_back(obj);
	return obj;
}

GameObject * GameObjectManager::newGameObjectBlueprint(unsigned int goID)
{
	GameObject* obj = new GameObject(_objectCount++);
	GameObject* other = getGameObject(goID);

	*obj = *other;

	_gameObjects.push_back(obj);
	return obj;
}

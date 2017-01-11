#include "InputManager.h"

#include <SDL\SDL.h>


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::update()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			keyReleased(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			mousePos.x = evnt.motion.x;
			mousePos.y = evnt.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			keyReleased(evnt.button.button);
			break;
		}
	}
}

void InputManager::keyPressed(unsigned int key)
{
	_keyMap[key] = true;
}

void InputManager::keyReleased(unsigned int key)
{
	_keyMap[key] = false;
}

bool InputManager::isKeyDown(unsigned int key)
{
	auto it = _keyMap.find(key);
	if (it != _keyMap.end())
		return it->second;
	else
		return false;
}

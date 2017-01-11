#pragma once

#include <unordered_map>
#include <glm\glm.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();
	
	void keyPressed(unsigned int key);
	void keyReleased(unsigned int key);
	bool isKeyDown(unsigned int key);

	glm::ivec2 mousePos;

private:
	std::unordered_map<unsigned int, bool> _keyMap;
};

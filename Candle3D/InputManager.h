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
	void setMousePos(float mouseX, float mouseY);

	glm::vec2 getMousePos() const { return _mousePos; }

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	glm::vec2 _mousePos;
};

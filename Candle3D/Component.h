#pragma once

#include <string>

class GameObject;

typedef std::string ComponentType;

class Component
{
public:

	Component() {}
	virtual ~Component() {}

	virtual void update() = 0;

	virtual ComponentType getID() = 0;
	
	void setParent(GameObject* parent) { _parent = parent; }

private:
	GameObject* _parent = nullptr;
};
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
	
	void setParent(GameObject* par) { parent = par; }

	GameObject* getParent() { return parent; }

	//--------------------------------//

protected:
	GameObject* parent = nullptr;
};
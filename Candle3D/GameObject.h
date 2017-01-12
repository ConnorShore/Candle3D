#pragma once

#include "Transform.h"
#include "Component.h"

#include <map>

class GameObject
{
public:
	GameObject(unsigned int id);
	~GameObject();

	void update();
	void attachComponent(Component* component);
	Component* removeComponent(ComponentType& type);

	Component* getComponent(const ComponentType& type);

	bool hasComponent(const ComponentType& type);

	unsigned int getID() const { return _id; }
	void setID(const unsigned int id) { _id = id; }

	Transform transform;

private:
	typedef std::map<const ComponentType, Component*> ComponentBag;
	ComponentBag _components;
	unsigned int _id;
};


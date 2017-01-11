#include "GameObject.h"


GameObject::GameObject(unsigned int id) : _id(id)
{
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	typedef ComponentBag::iterator iter;
	for (iter it = _components.begin(); it != _components.end(); it++){
		it->second->update();
	}
}

void GameObject::attachComponent(Component * component)
{
	component->setParent(this);
	_components.insert(std::make_pair(component->getID(), component));
}

Component* GameObject::removeComponent(ComponentType & type)
{
	auto mit =_components.find(type);
	if (mit == _components.end()) {
		printf("Component does not exist within object\n");
		return nullptr;
	}

	_components.erase(mit);
}

Component* GameObject::getComponent(const ComponentType& type)
{
	auto mit = _components.find(type);
	if (mit == _components.end())
		printf("Cannot find component%s", type);

	return mit->second;
}

bool GameObject::hasComponent(const ComponentType& type)
{
	auto mit = _components.find(type);
	if (mit == _components.end())
		return false;
	return true;
}
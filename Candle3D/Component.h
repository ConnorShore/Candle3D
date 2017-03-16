#pragma once

#include <string>
#include <vector>


class GameObject;

typedef std::string ComponentType;

class Component
{
public:

	Component() {}
	virtual ~Component() {}

	virtual void update() = 0;

	virtual ComponentType getID() = 0;
	
	void addTag(std::string& tag) { tags.push_back(tag); }
	void setParent(GameObject* par) { parent = par; }

	GameObject* getParent() { return parent; }

	bool hasTag(std::string& tag)
	{
		for (int i = 0; i < tags.size(); i++) {
			if (tags[i] == tag)
				return true;
		}
		return false;
	}

	//--------------------------------//

protected:
	GameObject* parent = nullptr;
	std::vector<std::string> tags;
};
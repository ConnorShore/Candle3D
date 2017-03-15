#pragma once

#include "..\Component.h"
#include <Bullet\btBulletDynamicsCommon.h>

enum ColliderType
{
	NONE, BOX, SPHERE, CYLINDER, CAPSULE, CONE
};

class ColliderComponent : public Component
{
public:
	virtual void update() override {}
	virtual ComponentType getID() override { return "collider"; }

	ColliderType colliderType;
	btCollisionShape* shape = nullptr;
};
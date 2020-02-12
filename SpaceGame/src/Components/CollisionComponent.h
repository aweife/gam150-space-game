#pragma once

#include "AEEngine.h"
#include "../SpaceGame/src/Systems/PhysicsSystem.h"

class CollisionComponent
{

public:
	// Constructor
	CollisionComponent() = default;

	// Destructor
	~CollisionComponent() = default;

	// Checking for Collision (AABB)
	bool checkforCollisionAABB(const AABB& obj1, const Vector2D& vel1,
		const AABB& obj2, const Vector2D& vel2);

	//// Checking for Collision (Circle)
	//bool checkforCollisionCircle();

	void Update();
};
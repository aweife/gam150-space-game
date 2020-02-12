#pragma once

#include "AEEngine.h"
#include "../Systems/PhysicsSystem.h"

class cCollision
{

public:
	// Constructor
	cCollision() = default;

	// Destructor
	~cCollision() = default;

	// Checking for Collision (AABB)
	bool checkforCollisionAABB(const AABB& obj1, const AEVec2& vel1,
		const AABB& obj2, const AEVec2& vel2);

	//// Checking for Collision (Circle)
	//bool checkforCollisionCircle();

	void Update();
};
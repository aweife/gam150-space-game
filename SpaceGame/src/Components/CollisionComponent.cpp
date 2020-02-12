/*********************************************************************************
* \file			CollisionComponent.cpp
* \author		Farzaana Binte Roslan
* \version		1.0
* \date			31/01/2020
* \par			Systems
* \note			Course: GAM150
* \brief		Physics system to control various physics manager
				-

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "CollisionComponent.h"
#include "../SpaceGame/src/Systems/PhysicsSystem.h"
#include <AEVec2.h>
#include "Math.h"


/*********************************************************************************
*
*  COLLISION COMPONENT FUNCTIONS
*
**********************************************************************************/

// Checking for Collision (AABB)
bool CollisionComponent::checkforCollisionAABB(const AABB& obj1, const Vector2D& vel1,
	const AABB& obj2, const Vector2D& vel2)
{
	// To check for collision detection between static rectangles, if the check returns no overlap, continue
	if ((obj1.max.x < obj2.min.x || obj1.min.x > obj2.max.x ||
		obj1.max.y < obj2.min.y || obj1.min.y > obj2.max.y) == false)
	{
		return true;
	}

	// Initialise variables and calculate the new velocity
	float tFirst = 0;
	float tLast = g_dt;
	float newVelocity_x = vel2.x - vel1.x;
	float newVelocity_y = vel2.y - vel1.y;
	float dFirst_x = obj1.min.x - obj2.max.x;
	float dLast_x = obj1.max.x - obj2.min.x;
	float dFirst_y = obj1.min.y - obj2.max.y;
	float dLast_y = obj1.max.y - obj2.min.y;

	// Working with one-dimention (x-axis)
	if (newVelocity_x < 0)
	{
		// Case 1 
		if (obj1.max.x > obj2.min.x)
		{
			return false;
		}

		// Case 4 
		if (obj1.max.x < obj2.min.x)
		{
			tFirst = max(dFirst_x / newVelocity_x, tFirst);
		}

		if (obj1.min.x < obj2.max.x)
		{
			tLast = min(dLast_x / newVelocity_x, tLast);
		}
	}

	if (newVelocity_x > 0)
	{
		// Case 2 
		if (obj1.min.x > obj2.max.x)
		{
			tFirst = max(dFirst_x / newVelocity_x, tFirst);
		}

		if (obj1.max.x > obj2.min.x)
		{
			tLast = min(dLast_x / newVelocity_x, tLast);
		}

		// Case 3 
		if (obj1.max.x < obj2.min.x)
		{
			return false;
		}
	}

	// Case 5
	if (tFirst > tLast)
	{
		return false;
	}

	// Working with one-dimention (x-axis)
	if (newVelocity_y < 0)
	{
		// Case 1 
		if (obj1.max.y > obj2.min.y)
		{
			return false;
		}

		// Case 4 
		if (obj1.max.y < obj2.min.y)
		{
			tFirst = max(dFirst_y / newVelocity_y, tFirst);
		}

		if (obj1.min.y < obj2.max.y)
		{
			tLast = min(dLast_y / newVelocity_y, tLast);
		}
	}

	if (newVelocity_y > 0)
	{
		// Case 2 
		if (obj1.min.y > obj2.max.y)
		{
			tFirst = max(dFirst_y / newVelocity_y, tFirst);
		}

		if (obj1.max.y > obj2.min.y)
		{
			tLast = min(dLast_y / newVelocity_y, tLast);
		}

		// Case 3 
		if (obj1.max.y < obj2.min.y)
		{
			return false;
		}
	}

	// Case 5
	if (tFirst > tLast)
	{
		return false;
	}

	return true;
}

//// Checking for Collision (Circle)
//bool CollisionComponent::checkforCollisionCircle()
//{
//	return false;
//
//}

void CollisionComponent::Update()
{

}
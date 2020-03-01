/*********************************************************************************
* \file			CollisionSystem.cpp
* \author		Farzaana Binte Roslan
* \version		1.0
* \date			31/01/2020
* \par			Systems
* \note			Course: GAM150
* \brief		Collision system to manage the component component

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "CollisionSystem.h"
#include <AEVec2.h>
#include "Math.h"
#include "../Global.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"

#include <iostream>							//Testing
/*********************************************************************************
*
*  COLLISION COMPONENT FUNCTIONS
*
**********************************************************************************/

// Checking for Collision (AABB)
bool AABBCollision(const AABB& obj1, const AEVec2& vel1,
	const AABB& obj2, const AEVec2& vel2)
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

	// Working with one-dimention (y-axis)
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

// Checking if both circles
bool CircleCircleCollision(const AABB& obj1, const AABB& obj2 )
{
	float distX = obj1.center.x - obj2.center.x;
	float distY = obj1.center.y - obj2.center.y; 
	float totalRadius = obj1.radius + obj2.radius;
	float totalDist = (distX * distX) + (distY * distY);

	// totaldist <= totalRadius ^ 2 (compare both distances)
	if (totalDist <= (totalRadius * totalRadius) )
	{
		return true;
	}
	else
	{
		// no collision
		return false;
	}
}

// Checking if 1 circle and 1 rectangle
bool RectangleCircleCollision(const AABB& circle, const AABB& rectangle)
{
	float rectLength = rectangle.max.x - rectangle.min.x;
	float rectHeight = rectangle.max.y - rectangle.min.y;

	float deltaX = circle.center.x - max(rectangle.center.x, min(circle.center.x, rectangle.center.x + rectLength));
	float deltaY = circle.center.y - max(rectangle.center.y, min(circle.center.y, rectangle.center.y + rectHeight));

	return (deltaX * deltaX + deltaY * deltaY) < (circle.radius * circle.radius);
}

/*********************************************************************************
*
* To check for which collision 
*
**********************************************************************************/
bool CollisionCheck(const AABB& obj1, const ColliderShape shape1, const AEVec2 vel1,
					const AEVec2 vel2,const ColliderShape shape2,const AABB& obj2)
{
	// if both objects bounding box are circle 
	if (shape1 == ColliderShape::CIRCLE && shape2 == ColliderShape::CIRCLE)
	{
		// use the function for both circle check
		CircleCircleCollision(obj1, obj2);

	}
	// if one rectangle and one circle
	else if (shape1 == ColliderShape::CIRCLE && shape2 == ColliderShape::RECTANGLE)
	{
		// use the function for rectangle - circle check
		RectangleCircleCollision(obj1, obj2);
	}
	// if both rectangles
	else if (shape1 == ColliderShape::RECTANGLE && shape2 == ColliderShape::RECTANGLE)
	{
		// use the function for AABB 
		AABBCollision(obj1, vel1, obj2, vel2);
	}

	// return no collision
	return false; 
}


/*********************************************************************************
*
*  Collision System Functions
*
**********************************************************************************/
void CollisionSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cCollision>());
	Core::Get().SetSystemSignature<CollisionSystem>(signature);
}

void CollisionSystem::Update()
{
	cCollision* collider;
	cRigidBody* rigidbody;
	cTransform* transform;

	cCollision* collider2;
	cRigidBody* rigidbody2;
	cTransform* transform2;

	// To set all the bounding boxes of each entity
	for (auto const& entity : entitiesList)
	{
		collider = Core::Get().GetComponent<cCollision>(entity);
		transform = Core::Get().GetComponent<cTransform>(entity);

		collider->_boundingBox.max.x = 0.5f * transform->_scale.x + transform->_position.x;
		collider->_boundingBox.max.y = 0.5f * transform->_scale.y + transform->_position.y;
		collider->_boundingBox.min.x = -0.5f * transform->_scale.x + transform->_position.x;
		collider->_boundingBox.min.y = -0.5f * transform->_scale.y + transform->_position.y;

		// Set the enum to rectangle
		collider->_bbShape = ColliderShape::RECTANGLE;
	}

	// To check for collision for each entity in the list
	for (auto const& entity1 : entitiesList)
	{
		collider = Core::Get().GetComponent<cCollision>(entity1);
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity1);
		transform = Core::Get().GetComponent<cTransform>(entity1);


		for (auto const& entity2 : entitiesList)
		{
			if (entity2 == entity1)
			{
				continue;
			}

			collider2 = Core::Get().GetComponent<cCollision>(entity2);
			rigidbody2 = Core::Get().GetComponent<cRigidBody>(entity2);
			transform2 = Core::Get().GetComponent<cTransform>(entity2);

			if (AABBCollision(collider->_boundingBox, rigidbody->_velocityVector, collider2->_boundingBox, rigidbody2->_velocityVector) == true)
			{
				rigidbody->_velocity = 10.0f;
				rigidbody2->_velocity = 10.0f;
				if (rigidbody->_tag == COLLISIONTAG::BULLET && rigidbody2->_tag == COLLISIONTAG::ENEMY )
				{
					printf("ENEMY HEALTH DECREASE\n");
					markedForDestruction.insert(entity1);
				}

				// if player and enemy colide with each other 
				// player and enemy's health will decrease 
				// angular velocity will apply
			}
		}
	}

	//Collision Resolution
	//Part 1 - Destruction of objects
	if (markedForDestruction.size() > 0)
	{
		for (auto const& entity : markedForDestruction)
		{
			Core::Get().EntityDestroyed(entity);
		}
		markedForDestruction.clear();
	}
	
}

void CollisionSystem::Render() {}
void CollisionSystem::OnComponentAdd(ENTITY) {}
void CollisionSystem::OnComponentRemove(ENTITY) {}
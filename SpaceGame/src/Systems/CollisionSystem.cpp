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
#include "CollisionSystem.h"                // Self header
#include <AEVec2.h>                         // for AEVec2
#include <iostream>							//For debug purposes
#include <array>                            // array container
#include <vector>                           // vector container
#include <limits>                           // limits

#include "../Managers/CameraManager.h"		// For screen shake
#include "../Math/Math.h"                   // Additional Math functions
#include "../Global.h"                      // g_dt
#include "../ECS/Core.h"                    // For ECS
#include "../Components/ComponentList.h"    // For component list

/*********************************************************************************
*
* OPERATOR OVERLOAD
*
*********************************************************************************/



/*********************************************************************************
*
* HELPER FUNCTIONS
*
*********************************************************************************/
using RectVertexArray = std::array<AEVec2, 4>; // the array to store 4 sides of the rectangle

float min = std::numeric_limits<float>::infinity();
float max = -std::numeric_limits<float>::infinity();

// Finding the minimum and maximum projections of each array on the axis 
AEVec2 vectorProjections(const RectVertexArray& vertices, const AEVec2& axis)
{
	// to check all the vertices for projection 
	for (auto& vertex : vertices)
	{
		float proj = MBMath_DotProduct(vertex, axis);
		if (proj < min)
		{
			min = proj;
		}

		if (proj > max)
		{
			max = proj;
		}

		return AEVec2{ min, max };
	}
}

// to check whether both vectors are overlapping
bool isOverlapping(const AEVec2 vec1, const AEVec2 vec2)
{
	return vec1.x <= vec2.y && vec1.y >= vec2.x;
}

// to get the overlap length 
float overlappingLength(const AEVec2 vec1, const AEVec2 vec2)
{
	if (!isOverlapping(vec1, vec2))
	{
		return 0.0f; 
	}
	
	return min(vec1.y, vec2.y) - max(vec1.y, vec2.y);
}

RectVertexArray getVertices(const Colliders& shape)
{
	// since its just a rectangle, vertices will be just 4 
	RectVertexArray vertices;
	for (size_t i = 0; i < 4; ++i)
	{
		vertices[i] = shape._point;
	}
	return vertices;
}

AEVec2 getPerpendicularAxis(const RectVertexArray& vertex, size_t index)
{
	float diffX = vertex[index + 1].x - vertex[index].x;
	float diffY = vertex[index + 1].y - vertex[index].y;
	AEVec2 vec{ diffX, diffY };

	assert(index >= 0 && index < 4);
	return MBMath_getNormalofVector(MBMath_getNormalizedVector(vec));
}


// to check whether the axes are parallel, if they are parallel, do not need to check
std::array<AEVec2, 4> getPerpendicularAxesCheck(const RectVertexArray& vertices1, const RectVertexArray& vertices2)
{
	std::array<AEVec2, 4> axes; 

	axes[0] = getPerpendicularAxis(vertices1, 0);
	axes[1] = getPerpendicularAxis(vertices1, 1);

	axes[2] = getPerpendicularAxis(vertices2, 0);
	axes[3] = getPerpendicularAxis(vertices2, 1);

	return axes;
}


/*********************************************************************************
*
*  COLLISION COMPONENT FUNCTIONS
*
**********************************************************************************/

// Checking for Collision (AABB)
bool AABBCollision(const Colliders& obj1, const AEVec2& vel1,
	               const Colliders& obj2, const AEVec2& vel2)
{
	// Initialise variables and calculate the new velocity
	float tFirst = 0;
	float tLast = g_dt;
	float newVelocity_x = vel2.x - vel1.x;
	float newVelocity_y = vel2.y - vel1.y;
	float dFirst_x = obj1.max.x - obj2.min.x;
	float dLast_x = obj1.min.x - obj2.max.x;
	float dFirst_y = obj1.max.y - obj2.min.y;
	float dLast_y = obj1.min.y - obj2.max.y;

	// To check for collision detection between static rectangles, if the check returns no overlap, continue
	if (obj1.max.x < obj2.min.x || obj1.min.x > obj2.max.x ||
		obj1.max.y < obj2.min.y || obj1.min.y > obj2.max.y)
	{
		// Working with one-dimention (x-axis)
		if (newVelocity_x < 0.0f)
		{
			// Case 1 
			if (obj1.min.x > obj2.max.x)
			{
				return false;
			}

			// Case 4 
			if (obj1.max.x < obj2.min.x)
			{
				tFirst = AEMax(dFirst_x / newVelocity_x, tFirst);
			}

			if (obj1.min.x < obj2.max.x)
			{
				tLast = AEMin(dLast_x / newVelocity_x, tLast);
			}
		}

		if (newVelocity_x > 0)
		{
			// Case 2 
			if (obj1.min.x > obj2.max.x)
			{
				tFirst = AEMax(dFirst_x / newVelocity_x, tFirst);
			}

			if (obj1.max.x > obj2.min.x)
			{
				tLast = AEMin(dLast_x / newVelocity_x, tLast);
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
				tFirst = AEMax(dFirst_y / newVelocity_y, tFirst);
			}

			if (obj1.min.y < obj2.max.y)
			{
				tLast = AEMin(dLast_y / newVelocity_y, tLast);
			}
		}

		if (newVelocity_y > 0)
		{
			// Case 2 
			if (obj1.min.y > obj2.max.y)
			{
				tFirst = AEMax(dFirst_y / newVelocity_y, tFirst);
			}

			if (obj1.max.y > obj2.min.y)
			{
				tLast = AEMin(dLast_y / newVelocity_y, tLast);
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
	}

	return true;
}

// Checking if both circles collision
bool CircleCircleCollision(const Colliders& obj1, const Colliders& obj2 )
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
bool RectangleCircleCollision(const Colliders& circle, const Colliders& rectangle)
{
	float rectLength = rectangle.max.x - rectangle.min.x;
	float rectHeight = rectangle.max.y - rectangle.min.y;

	float deltaX = circle.center.x - max(rectangle.center.x, min(circle.center.x, rectangle.center.x + rectLength));
	float deltaY = circle.center.y - max(rectangle.center.y, min(circle.center.y, rectangle.center.y + rectHeight));

	if ( (deltaX * deltaX + deltaY * deltaY) < (circle.radius * circle.radius) )
	{
		return true;
	}
	else
	{
		return false;
	}
}


// find the overlap 
float minOverlap = std::numeric_limits<float>::infinity();

bool SATCollision(const Colliders& obj1, const Colliders& obj2, AEVec2 mtv)
{
	RectVertexArray vertices1 = getVertices(obj1);
	RectVertexArray vertices2 = getVertices(obj2);
	std::array<AEVec2, 4> axes = getPerpendicularAxesCheck(vertices1, vertices2);

	for (auto& axis : axes)
	{
		AEVec2 proj1 = vectorProjections(vertices1, axis);
		AEVec2 proj2 = vectorProjections(vertices2, axis);

		float overlap = overlappingLength(proj1, proj2);
		if (overlap == 0.0f)
		{
			return false;
		}
		else
		{
			if (overlap < minOverlap)
			{
				minOverlap = overlap; 
				mtv.x = axis.x * minOverlap;
				mtv.y = axis.y * minOverlap;
			}
		}
	}
		
	float diffVec_x = obj1.center.x - obj2.center.x;
	float diffVec_y = obj1.center.y - obj2.center.y;
	AEVec2 diffVec{ diffVec_x, diffVec_y };

	bool notSameDirection = MBMath_DotProduct(diffVec, mtv) < 0;
	if (notSameDirection)
	{
		float nmtv_x = -(mtv.x);	
		float nmtv_y = -(mtv.y);
		AEVec2 nmtv{ nmtv_x, nmtv_y };
		mtv = nmtv; 
	}
	return true;
}




/*********************************************************************************
*
* To check for which collision 
*
**********************************************************************************/
bool CollisionCheck(const Colliders& obj1, const ColliderShape shape1, const AEVec2 vel1,
					const Colliders& obj2,const ColliderShape shape2, const AEVec2 vel2)
{
	// if both objects bounding box are circle 
	if (shape1 == ColliderShape::CIRCLE && shape2 == ColliderShape::CIRCLE)
	{
		// use the function for both circle check
		return CircleCircleCollision(obj1, obj2);

	}
	// if one rectangle and one circle
	else if (shape1 == ColliderShape::CIRCLE && shape2 == ColliderShape::RECTANGLE)
	{
		// use the function for rectangle - circle check
		return RectangleCircleCollision(obj1, obj2);
	}
	// if both rectangles
	else if (shape1 == ColliderShape::RECTANGLE && shape2 == ColliderShape::RECTANGLE)
	{
		// use the function for AABB 
		return AABBCollision(obj1, vel1, obj2, vel2);
	}
	else if (shape1 == ColliderShape::RECTANGLE_OBB && shape2 == ColliderShape::RECTANGLE_OBB)
	{
		if (AABBCollision(obj1, vel1, obj2, vel2) == true)
		{
			SATCollision(obj1, obj2, vel1);
		}
		else
		{
			return false;
		}
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

			// For to check which collision
			if (CollisionCheck(collider->_boundingBox, collider->_bbShape, 
				               rigidbody->_velocityVector, collider2->_boundingBox,
				               collider2->_bbShape,rigidbody2->_velocityVector) == true)
			{

				// if player and enemy collide with each other 
				// player and enemy's health will decrease 
				// angular velocity will apply
				if (rigidbody->_tag == COLLISIONTAG::PLAYER && rigidbody2->_tag == COLLISIONTAG::ENEMY)
				{
					CameraManager::StartCameraShake();
					printf("Enemy health decrease lmao\n");

					// for player's bounce off
					rigidbody->_angularVelocity.x = -20.0f;
					rigidbody->_angularVelocity.y = -20.0f;
					rigidbody->_velocityVector.x += rigidbody->_angularVelocity.x;
					rigidbody->_velocityVector.y += rigidbody->_angularVelocity.y;

					// for enemy's bounce off
					rigidbody2->_angularVelocity.x = -50.0f;
					rigidbody2->_angularVelocity.y = -50.0f;
					rigidbody2->_velocityChangeVector = rigidbody2->_angularVelocity;
				}
				
				// if bullet collide with enemy
				if (rigidbody->_tag == COLLISIONTAG::BULLET && rigidbody2->_tag == COLLISIONTAG::ENEMY )
				{
					CameraManager::StartCameraShake();
					printf("ENEMY HEALTH DECREASE\n");
					markedForDestruction.insert(entity1);
				}

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
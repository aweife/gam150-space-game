/*********************************************************************************
* \file			PhysicsSystem.cpp
* \author		Farzaana Binte Roslan
* \version		1.0
* \date			31/01/2019
* \par			Systems
* \note			Course: GAM150
* \brief		Physics system to control various physics manager
				- 

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "PhysicsSystem.h"
#include <AEVec2.h>
#include "Math.h"

/*********************************************************************************
*
*  GLOBAL VARIABLES (FOR EULER'S METHOD <TEST>)
*
**********************************************************************************/
float thrust = 100.0f; 
float displacement = 50.0f;
float _velocity = 30.0f;
float _mass = 30.0f;

/*********************************************************************************
*
*  RIGIDBODY COMPONENT FUNCTIONS
*
**********************************************************************************/
// Constructor
RigidBodyComponent::RigidBodyComponent() : mass{ 30.0f }, inertia{ 10.0f }, 
										   inertiaInverse{5.0f}, position{ 0.0f, 0.0f },
										   velocity{0.0f, 0.0f}, angularVelocity{0.0f, 0.0f}
{

}

// Using default destructor

// Getters 
float RigidBodyComponent::getMass()
{
	return mass;
}

float RigidBodyComponent::getInertia()
{
	return inertia;
}

float RigidBodyComponent::getInertiaInverse()
{
	return inertiaInverse;
}

Vector2D RigidBodyComponent::getPosition()
{
	return position;
}

Vector2D RigidBodyComponent::getVelocity()
{
	return velocity;
}

Vector2D RigidBodyComponent::getAngularVelocity()
{
	return angularVelocity;
}

// Initialise rigidbody
void RigidBodyComponent::Initialize(RigidBodyComponent body)
{
	// Set initial position
	body.position.x = 0.0f;
	body.position.y = 0.0f;

	// Set initial velocity 
	body.velocity.x = 0.0f;
	body.velocity.y = 0.0f; 

	// Set angular velocity
	body.angularVelocity.x = 0.0f;
	body.angularVelocity.y = 0.0f;
}

// Update the Rigidbody accordingly
void RigidBodyComponent::Update()
{
	// Euler's method (tested using global variables)
	float force;				// total force
	float acceleration;			// acceleration of the ship
	float newVelocity;			// new velocity at the time t + dt
	float newDisplacement;		// new displacement at the time t + dt

	// Calculate total force 
	force = (thrust - (displacement * _velocity));

	// Calculate the acceleration 
	acceleration = force / _mass;

	// Calculate the new velocity at time t + dt 
	// V is the velocity at time t
	newVelocity = _velocity + acceleration * g_dt;

	// Calculate the new displacement at time t + dt
	newDisplacement = displacement + newVelocity * g_dt;

	// Updating the old velocity
	_velocity = newVelocity;
	displacement = newDisplacement;

	// Trying a physics method other than euler's method


}



/*********************************************************************************
*
*  COLLISION COMPONENT FUNCTIONS
*
**********************************************************************************/

// Constructor
CollisionComponent::CollisionComponent()
{

}

// Destructor
CollisionComponent::~CollisionComponent()
{

}

// Checking for Collision (AABB)
bool CollisionComponent::checkforCollisionAABB(const AABB & obj1, const Vector2D & vel1, 
	                                           const AABB & obj2, const Vector2D & vel2)
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

// Checking for Collision (Circle)
bool CollisionComponent::checkforCollisionCircle()
{
	return false;

}
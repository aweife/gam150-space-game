/*********************************************************************************
* \file			PhysicsSystem.cpp
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
#include "PhysicsSystem.h"
#include <AEVec2.h>
#include "Math.h"
#include "../ECS/Core.h"

extern Core coreInstance;

/*********************************************************************************
*
*  GLOBAL VARIABLES (FOR EULER'S METHOD <TEST>)
*
**********************************************************************************/
float thrust = 500.0f;
float drag = 5.0f;
float displacement = 50.0f;
float _velocity = 30.0f;
float _mass = 30.0f;

void PhysicsSystem::Init(cRigidBody body)
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

void PhysicsSystem::Update()
{
	cTransform* transform;
	cRigidBody* rigidbody;
	
	for (auto const& entity : entitiesList)
	{
		transform = coreInstance.GetComponent<cTransform>(entity);
		rigidbody = coreInstance.GetComponent<cRigidBody>(entity);

		// Euler's method (tested using global variables)
		// Trying Runge-Kutta method with basic Euler's
		float force;				// total force
		float acceleration;			// acceleration of the ship
		float newVelocity;			// new velocity at the time t + dt
		float newDisplacement;		// new displacement at the time t + dt
		float k1, k2, k3, k4;

		// Calculate total force 
		force = (thrust - (drag * _velocity));

		// Calculate the acceleration 
		acceleration = force / _mass;
		k1 = g_dt * acceleration;


		force = (thrust - (drag * (_velocity + k1 / 2)));
		acceleration = force / _mass;
		k2 = g_dt * acceleration;

		force = (thrust - (drag * (_velocity + k2 / 2)));
		acceleration = force / _mass;
		k3 = g_dt * acceleration;

		force = (thrust - (drag * (_velocity + k3)));
		acceleration = force / _mass;
		k4 = g_dt * acceleration;

		// Calculate the new velocity at time t + dt 
		// V is the velocity at time t
		newVelocity = _velocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		// Calculate the new displacement at time t + dt
		newDisplacement = displacement + newVelocity * g_dt;

		// Updating the old velocity
		_velocity = newVelocity;
		displacement = newDisplacement;

		transform->position.x += rigidbody->velocity.x;
		transform->position.y += rigidbody->velocity.y;
	}
	

}
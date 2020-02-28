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
#include "../Global.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"

/*********************************************************************************
*
*  GLOBAL VARIABLES (FOR EULER'S METHOD <TEST>)
*
**********************************************************************************/
float thrust = 500.0f;
float drag = 5.0f;
float displacement = 50.0f;
float velocity = 30.0f;
float mass = 30.0f;

void PhysicsSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	Core::Get().SetSystemSignature<PhysicsSystem>(signature);
}

void PhysicsSystem::Update()
{
	cTransform* transform;
	cRigidBody* rigidbody;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity);

		// Euler's method (tested using global variables)
		// Trying Runge-Kutta method with basic Euler's
		//float force;				// total force
		//float acceleration;			// acceleration of the ship
		//float newVelocity;			// new velocity at the time t + dt
		//float newDisplacement;		// new displacement at the time t + dt
		//float k1, k2, k3, k4;

		//// Calculate total force 
		//force = (thrust - (drag * velocity));

		//// Calculate the acceleration 
		//acceleration = force / mass;
		//k1 = g_dt * acceleration;

		//force = (thrust - (drag * (velocity + k1 / 2)));
		//acceleration = force / mass;
		//k2 = g_dt * acceleration;

		//force = (thrust - (drag * (velocity + k2 / 2)));
		//acceleration = force / mass;
		//k3 = g_dt * acceleration;

		//force = (thrust - (drag * (velocity + k3)));
		//acceleration = force / mass;
		//k4 = g_dt * acceleration;

		//// Calculate the new velocity at time t + dt 
		//// V is the velocity at time t
		//newVelocity = velocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		//// Calculate the new displacement at time t + dt
		//newDisplacement = displacement + newVelocity * g_dt;

		//// Updating the old velocity
		//velocity = newVelocity;
		//displacement = newDisplacement;

		// -----------------------------------------------------------------------
		// Currently whats working
		// -----------------------------------------------------------------------

		

		// Add the new frame velocity change onto the current velocity
		AEVec2Add(&rigidbody->_velocityVector, &rigidbody->_velocityVector, &rigidbody->_velocityChangeVector);
		// Reset the change in velocity for next frame
		AEVec2Zero(&rigidbody->_velocityChangeVector);

		// Set a cap onto the current velocity
		if (AEVec2Length(&rigidbody->_velocityVector) >= rigidbody->_velocityCap)
		{
			AEVec2Scale(&rigidbody->_velocityVector, &rigidbody->_velocityVector, 0.99f);		//Smootly reduce velocity
		}

		// Calculate velocity magnitude
		rigidbody->_velocity = AEVec2Length(&rigidbody->_velocityVector);

		// Calculate normalised velocity vector.....Check if the _velocityVector not (0,0) 
		if (!(rigidbody->_velocityVector.x < FLT_EPSILON && rigidbody->_velocityVector.x > -FLT_EPSILON &&
			rigidbody->_velocityVector.y < FLT_EPSILON && rigidbody->_velocityVector.y > -FLT_EPSILON))
		{
			AEVec2Normalize(&rigidbody->_velocityDirection, &rigidbody->_velocityVector);
		}

		// Apply displacement on current position
		transform->_position.x += rigidbody->_velocityVector.x * g_dt;
		transform->_position.y += rigidbody->_velocityVector.y * g_dt;
	}
}
void PhysicsSystem::OnComponentAdd(ENTITY) {};
void PhysicsSystem::OnComponentRemove(ENTITY) {};

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
#include "../Math/Math.h"
#include <math.h>
#include "../Global.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"
#include "../Tools/Editor.h"


bool foranglecheck(AEVec2 currdir, AEVec2 newdir)
{
	float angle = AERadToDeg(acosf(MBMath_DotProduct(currdir, newdir)));

	if (angle > 90)
	{
		return true;
	}
	else
	{
		return false;
	}
}


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


		// -----------------------------------------------------------------------
		// Currently whats working
		// -----------------------------------------------------------------------

		// Add the new frame velocity change onto the current velocity
		AEVec2Add(&rigidbody->_velocityVector, &rigidbody->_velocityVector, &rigidbody->_velocityChangeVector);
		// Reset the change in velocity for next frame
		AEVec2Zero(&rigidbody->_velocityChangeVector);

		// Set a cap onto the current velocity
		//if (AEVec2Length(&rigidbody->_velocityVector) >= rigidbody->_velocityCap)
		//{
			
		//}

		// Calculate velocity magnitude
		rigidbody->_velocity = AEVec2Length(&rigidbody->_velocityVector);
		//Editor_TrackVariable("Velocity: ", rigidbody->_velocity)

		// Calculate normalised velocity vector.....Check if the _velocityVector not (0,0) 
		if (!(rigidbody->_velocityVector.x < FLT_EPSILON && rigidbody->_velocityVector.x > -FLT_EPSILON &&
			rigidbody->_velocityVector.y < FLT_EPSILON && rigidbody->_velocityVector.y > -FLT_EPSILON))
		{
			AEVec2Normalize(&rigidbody->_velocityDirection, &rigidbody->_velocityVector);
		}

		// if the velocity hits the velocity cap
		if (rigidbody->_velocity > rigidbody->_velocityCap)
			rigidbody->_velocity = rigidbody->_velocityCap;

		// Add onto the velocity
		AEVec2Scale(&rigidbody->_velocityVector, &rigidbody->_velocityDirection, rigidbody->_velocity);

		/***************
		* AI
		****************/
		// Addition of forces to final calculation
		rigidbody->_aiSteeringVector.x = rigidbody->_aiSteeringVector.x / rigidbody->_mass;
		rigidbody->_aiSteeringVector.y = rigidbody->_aiSteeringVector.y / rigidbody->_mass;


		// add steering vector into the velocity vector
		AEVec2Add(&rigidbody->_velocityVector, &rigidbody->_velocityVector, &rigidbody->_aiSteeringVector);

		// check if the collision is bigger than the other vectors
		if (rigidbody->_collisionVector.x > rigidbody->_velocityVector.x &&
			rigidbody->_collisionVector.y > rigidbody->_velocityVector.y)
		{
			// to set the current velocity vector to the collision vector, and decrement the collision vector 
			--rigidbody->_collisionVector.x;
			--rigidbody->_collisionVector.y;
		}

		//add the gravitational vector into the velocity vector
		AEVec2Add(&rigidbody->_velocityVector, &rigidbody->_velocityVector, &rigidbody->_gravityVelocity);

		//Smootly reduce velocity
		AEVec2Scale(&rigidbody->_velocityVector, &rigidbody->_velocityVector, 0.995f);

		// Apply displacement on current position
		transform->_position.x += rigidbody->_velocityVector.x * g_dt;
		transform->_position.y += rigidbody->_velocityVector.y * g_dt;
	}


}
void PhysicsSystem::OnComponentAdd(ENTITY) {};
void PhysicsSystem::OnComponentRemove(ENTITY) {};

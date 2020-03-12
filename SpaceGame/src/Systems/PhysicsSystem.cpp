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


bool foranglecheck(const AEVec2 currdir, const AEVec2 newdir)
{
	float angle = AERadToDeg(acosf(MBMath_DotProduct(currdir, newdir)));
	//Editor_TrackVariable("player angle ", angle);
	return (angle > PI / 2.0f);
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
	cTransform* trans;
	cRigidBody* rb;

	for (auto const& entity : entitiesList)
	{
		trans = Core::Get().GetComponent<cTransform>(entity);
		rb = Core::Get().GetComponent<cRigidBody>(entity);

		/*if (foranglecheck(rb->_currentVelocityDirection, rb->_velocityDirection))
		{
			rb->_velocity *= 0.995f;

			if (rb->_velocity < 1.0f)
				rb->_currentVelocityDirection = rb->_velocityDirection;
		}*/

		// Apply "air friction"
		rb->_velocity *= 0.995f;

		// if the velocity hits the velocity cap
		if (rb->_velocity > rb->_velocityCap)
			rb->_velocity *= 0.97f;

		// Calculate current velocity vector based on velocity and direction
		AEVec2Scale(&rb->_velocityVector, &rb->_velocityDirection, rb->_velocity * g_dt);

		// -----------------------------------------------------------------------
		//	Physics calculation: Sum of all extra forces
		// -----------------------------------------------------------------------

		// Add collision vector into the velocity vector
		AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_collisionVector);
		//Smootly reduce velocity
		AEVec2Scale(&rb->_collisionVector, &rb->_collisionVector, 0.9f);
				
		// Affect steering force by mass
		//AEVec2Scale(&rb->_steeringVector, &rb->_steeringVector, 1.0f/rb->_mass);

		// Add player force into the velocity vector
		AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_velocityChangeVector);

		// Add steering force into the velocity vector
		AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_steeringVector);

		// Add the gravitational force into the velocity vector
		AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_gravityVelocity);

		// Finally, add velocity to transform
		AEVec2Add(&trans->_position, &trans->_position, &rb->_velocityVector);

		// Update directional vector
		if (fabs(rb->_velocityVector.x + rb->_velocityVector.y) > FLT_EPSILON)
			AEVec2Normalize(&rb->_velocityDirection, &rb->_velocityVector);

		//// -----------------------------------------------------------------------
		//// Currently whats working
		//// -----------------------------------------------------------------------

		//// Add the new frame velocity change onto the current velocity
		//AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_velocityChangeVector);
		//// Reset the change in velocity for next frame
		//AEVec2Zero(&rb->_velocityChangeVector);

		//// Set a cap onto the current velocity
		////if (AEVec2Length(&rigidbody->_velocityVector) >= rigidbody->_velocityCap)
		////{
		//	
		////}

		//// Calculate velocity magnitude
		////rigidbody->_velocity = AEVec2Length(&rigidbody->_velocityVector);
		////Editor_TrackVariable("Velocity: ", rigidbody->_velocity)

		//// Calculate normalised velocity vector.....Check if the _velocityVector not (0,0) 
		//if (!(rb->_velocityVector.x < FLT_EPSILON && rb->_velocityVector.x > -FLT_EPSILON &&
		//	rb->_velocityVector.y < FLT_EPSILON && rb->_velocityVector.y > -FLT_EPSILON))
		//{
		//	AEVec2Normalize(&rb->_velocityDirection, &rb->_velocityVector);
		//}

		//// if the velocity hits the velocity cap
		//if (rb->_velocity > rb->_velocityCap)
		//	rb->_velocity *= 0.99f;

		//// Add onto the velocity
		//AEVec2Scale(&rb->_velocityVector, &rb->_velocityDirection, rb->_velocity);

		///***************
		//* AI
		//****************/
		//// Addition of forces to final calculation
		//rb->_aiSteeringVector.x = rb->_aiSteeringVector.x / rb->_mass;
		//rb->_aiSteeringVector.y = rb->_aiSteeringVector.y / rb->_mass;


		//// add steering vector into the velocity vector
		//AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_aiSteeringVector);

		//// check if the collision is bigger than the other vectors
		//if (rb->_collisionVector.x > rb->_velocityVector.x &&
		//	rb->_collisionVector.y > rb->_velocityVector.y)
		//{
		//	// to set the current velocity vector to the collision vector, and decrement the collision vector 
		//	--rb->_collisionVector.x;
		//	--rb->_collisionVector.y;
		//}

		////add the gravitational vector into the velocity vector
		//AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &rb->_gravityVelocity);

		////Smootly reduce velocity
		//AEVec2Scale(&rb->_velocityVector, &rb->_velocityVector, 0.9f);

		//// Apply displacement on current position
		//trans->_position.x += rb->_velocityVector.x * g_dt;
		//trans->_position.y += rb->_velocityVector.y * g_dt;
	}


}
void PhysicsSystem::OnComponentAdd(ENTITY) {};
void PhysicsSystem::OnComponentRemove(ENTITY) {};

/*********************************************************************************
* \file			cRigidBody.cpp
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
#include "cRigidBody.h"
#include <AEVec2.h>
#include "Math.h"
#include "../Global.h"

/*********************************************************************************
*
*  RIGIDBODY COMPONENT FUNCTIONS
*
**********************************************************************************/
// Constructor
cRigidBody::cRigidBody(float mass, float velocity, float velocityCap, float acceleration, float rotateVelocity)
	: _mass{mass}, _velocity{velocity}, _velocityCap{velocityCap}, _acceleration{acceleration}, _rotateVelocity{rotateVelocity},
	_velocityVector{ 0,0 }, _angularVelocity{ 0,0 }, _velocityChangeVector{ 0,0 }, _velocityDirection{ 0,0 }
{

}


float cRigidBody::calculateVelwithAcc(float velocity)
{
	float acceleration = velocity / g_dt;
	float newVelocity = (acceleration * g_dt) + velocity; 
	newVelocity = newVelocity * 0.99f; 
	return newVelocity;
}

// Using default destructor


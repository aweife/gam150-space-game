/*********************************************************************************
* \file			RigidBodyComponent.cpp
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
#include "RigidBodyComponent.h"
#include <AEVec2.h>
#include "Math.h"
#include "../SpaceGame/src/Global.h"


/*********************************************************************************
*
*  RIGIDBODY COMPONENT FUNCTIONS
*
**********************************************************************************/
// Constructor
RigidBodyComponent::RigidBodyComponent() : mass{ 30.0f }, inertia{ 10.0f },
inertiaInverse{ 5.0f }, position{ 0.0f, 0.0f },
velocity{ 0.0f, 0.0f }, angularVelocity{ 0.0f, 0.0f }
{

}

// Using default destructor


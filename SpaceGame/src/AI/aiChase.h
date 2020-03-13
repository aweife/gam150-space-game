/**********************************************************************************
* \file			aiChase.h
* \brief		??
* \author		Wei Feng, Ang, 100% Code Contribution
*
*				Long Description
*				- 
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"

class aiChase : public aiBase
{
public:
	virtual void Run(const aiBlackBoard&, the_variant&) override;
private:
	cTransform* trans;
	cRigidBody* rb;

	// Arrival at target
	float attackRange;
	float maxSpeed;
	float acceleration;
	float rotationSpeed;
	float wanderAngle;
	float chaseTimer;
};

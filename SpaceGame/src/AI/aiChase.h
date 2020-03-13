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

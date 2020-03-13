#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"

class aiPursuit : public aiBase
{
public:
	virtual void Run(const aiBlackBoard&, the_variant&) override;
private:
	cTransform* trans;
	cRigidBody* rb;

	cTransform* ptrans;
	cRigidBody* prb;

	// Arrival at target
	float attackRange;
	float maxSpeed;
	float acceleration;
	float rotationSpeed;
	float wanderAngle;

	AEVec2 futurePosition;
	AEVec2 targetDistance;
	float distanceFromTarget;
};
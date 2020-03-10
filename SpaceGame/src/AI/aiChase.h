#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"

class aiChase : public aiBase
{
public:
	virtual void Run( const aiBlackBoard&, the_variant& ) override;
private:
	cTransform* trans;
	cRigidBody* rb;

	// Arrival at target
	float minDistance;
	float attackRange;
	float maxSpeed;
	float acceleration;

	void RotateToTarget(const aiBlackBoard&);
	void MoveToTarget(const aiBlackBoard&);
};

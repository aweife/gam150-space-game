#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"
#include "../Components/cWeapon.h"

class aiAttack : public aiBase
{
public:
	virtual void Run(const aiBlackBoard&, the_variant&) override;
private:
	cTransform* trans;
	cRigidBody* rb;
	cRangeWeapon* rwp;

	// Variables
	float rotationSpeed;

	// State transition checks
	float minDistance;
	float maxDistance;

	void AimAtTarget(const aiBlackBoard&);
	bool TargetInRange(const aiBlackBoard&);
	void Attack();
};
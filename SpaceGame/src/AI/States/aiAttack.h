#pragma once

#include "aiBase.h"
#include "../../Components/cTransform.h"
#include "../../Components/cRigidBody.h"
#include "../../Components/cWeapon.h"

class aiAttack : public aiBase
{
public:
	virtual void Run(aiBlackBoard&, aiStateList&) override;
private:

	// Component this state needs
	cTransform* trans;
	cRigidBody* rb;
	cRangeWeapon* rwp;

	// State transition checks
	float _minDistance;
	float _maxDistance;

	void AimAtTarget(const aiBlackBoard&);
	bool TargetInRange(const aiBlackBoard&);
	bool TargetTooClose(const aiBlackBoard& bb);
	void Attack();
};
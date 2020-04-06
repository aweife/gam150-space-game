#pragma once

#include "aiBase.h"
#include "../../Components/cWeapon.h"

class aiPursuitAttack : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	void Attack();

	// Extra components this state needs
	cTransform* ptrans;
	cRigidBody* prb;
	cRangeWeapon* rwp;

	// State variables
	float _pursuitTimer;
	float _positionPrediction;

	AEVec2 _futureTargetPosition;
	AEVec2 _targetPosition;
	float _distanceFromTarget;
};
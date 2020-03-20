#pragma once

#include "aiBase.h"
#include "../../Components/cWeapon.h"

class aiAttack : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	// Extra components this state needs
	cRangeWeapon* rwp;

	// State transition checks
	float _minDistance;
	float _maxDistance;

	void Attack();
};
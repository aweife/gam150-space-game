#pragma once

#include "bossBase.h"
#include "../../Components/cWeapon.h"

class bossNormal : public bossBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(bossAttackList&) override;

	void Attack(aiBlackBoard& );

	// Extra components this state needs
	cRangeWeapon* rwp;

	// State variables
};
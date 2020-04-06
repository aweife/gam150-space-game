/**********************************************************************************
* \file			bossRapid.h
* \brief		Boss move state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Allow the boss to attack rapidly
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "bossBase.h"
#include "../../Components/cWeapon.h"

class bossRapid : public bossBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(bossAttackList&) override;

	void Attack(aiBlackBoard&);

	// Extra components this state needs
	cRangeWeapon* rwp;

	// State variables
	float _attackDuration;
	float _attackCooldown;
	float _delayBetweenAttacks;
	int _numberOfAttacks;
};
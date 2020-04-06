/**********************************************************************************
* \file			bossHoming.h
* \brief		Boss homing state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss homing state
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "bossBase.h"
#include "../../Components/cWeapon.h"

class bossHoming : public bossBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(bossAttackList&) override;

	void Attack(aiBlackBoard&);

	// Extra components this state needs
	cRangeWeapon* rwp;

	// State variables
};
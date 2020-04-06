/**********************************************************************************
* \file			aiAttack.h
* \brief		AI attack state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise attack state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
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
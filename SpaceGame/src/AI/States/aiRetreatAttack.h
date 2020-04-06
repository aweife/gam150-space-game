/**********************************************************************************
* \file			aiRetreatAttack.h
* \brief		AI retreat attack state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise retreat attack state of AI
*				- Allow ai to attack when retreating
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"
#include "AEVec2.h"
#include "../../Components/cWeapon.h"

class aiRetreatAttack : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	// Extra components this state needs
	cRangeWeapon* rwp;

	// State checks
	float _safeDistance;
	AEVec2 _safePosition;

	void FindSafePosition(const aiBlackBoard& bb);
	float TurnToTarget(const float& self, const AEVec2& target);
	void Attack();
};
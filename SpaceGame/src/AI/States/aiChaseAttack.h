/**********************************************************************************
* \file			aiChaseAttack.h
* \brief		AI chase attack state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise chase attack state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"
#include "../../Components/cWeapon.h"

class aiChaseAttack : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;
	void Attack();

	// Extra components this state needs
	cRangeWeapon* rwp;

	// State variables
};
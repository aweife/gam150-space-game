/**********************************************************************************
* \file			bossMove.h
* \brief		Boss move state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Moves the boss slowly towards the target
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "bossBase.h"

class bossMove : public bossBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(bossAttackList&) override;

	// Extra components this state needs

	// State variables
	float _moveDuration;
};
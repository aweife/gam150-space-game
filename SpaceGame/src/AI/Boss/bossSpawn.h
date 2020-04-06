/**********************************************************************************
* \file			bossSpawn.h
* \brief		Boss spawn
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss spawning
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "bossBase.h"
#include "AEVec2.h"

class bossSpawn : public bossBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(bossAttackList&) override;

	// Extra components this state needs

	// State variables
	AEVec2 _maxSize;
	float _sizeRatioX;
	float _sizeRatioY;
};
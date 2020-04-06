/**********************************************************************************
* \file			aiRetreat.h
* \brief		AI retreat state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise retreat state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"
#include "AEVec2.h"

class aiRetreat : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	// Extra components this state needs

	// State checks
	float _safeDistance;
	AEVec2 _safePosition;

	void FindSafePosition(const aiBlackBoard& bb);
	float TurnToTarget(const float& self, const AEVec2& target);
};
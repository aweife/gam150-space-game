/**********************************************************************************
* \file			aiPursuit.h
* \brief		AI pursuit state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise pursuit state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"

class aiPursuit : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	// Extra components this state needs
	cTransform* ptrans;
	cRigidBody* prb;

	// State variables
	float _pursuitTimer;
	float _positionPrediction;

	AEVec2 _futureTargetPosition;
	AEVec2 _targetPosition;
	float _distanceFromTarget;
};
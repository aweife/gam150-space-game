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
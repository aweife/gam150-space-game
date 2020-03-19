#pragma once

#include "aiBase.h"
#include "../../Components/cTransform.h"
#include "../../Components/cRigidBody.h"

class aiPursuit : public aiBase
{
public:
	virtual void Run(aiBlackBoard&, aiStateList&) override;
private:

	// Component this state needs
	cTransform* trans;
	cRigidBody* rb;

	cTransform* ptrans;
	cRigidBody* prb;

	float _pursuitTimer;
	float _positionPrediction;

	AEVec2 _futureTargetPosition;
	AEVec2 _targetPosition;
	float _distanceFromTarget;
};
#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"
#include "AEEngine.h"

class aiRetreat : public aiBase
{
public:
	virtual void Run( const aiBlackBoard&, the_variant& ) override;
private:
	cTransform* trans;
	cRigidBody* rb;

	AEVec2 _targetPosition;
	float _safeDistance;

	void FindSafePosition(const aiBlackBoard& bb);
	void Flee();
};
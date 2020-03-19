#pragma once

#include "aiBase.h"
#include "../../Components/cTransform.h"
#include "../../Components/cRigidBody.h"
#include "AEVec2.h"

class aiRetreat : public aiBase
{
public:
	virtual void Run( aiBlackBoard&, aiStateList& ) override;
private:

	// Component this state needs
	cTransform* trans;
	cRigidBody* rb;

	float _safeDistance;
	AEVec2 _safePosition;
	void FindSafePosition(const aiBlackBoard& bb);
};
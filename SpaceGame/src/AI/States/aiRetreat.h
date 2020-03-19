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
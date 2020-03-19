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
	AEVec2 _initialScale;
};
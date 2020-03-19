#pragma once

#include "bossBase.h"

class bossNormal : public bossBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(bossAttackList&) override;

	// Extra components this state needs

	// State variables
};
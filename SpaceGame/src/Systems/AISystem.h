#pragma once

#include "System.h"

// For Blackboard
#include "../Player/PlayerManager.h"
#include "../AI/aiBlackBoard.h"


class AISystem : public System
{
public:
	AISystem() = default;
	~AISystem() = default;
	void Init() override;
	void Render() override {};
	void Update() override;
	void OnComponentAdd(ENTITY) override;
	void OnComponentRemove(ENTITY) override;

private:
	void UpdateBlackboard(aiBlackBoard&, ENTITY);
};
#pragma once

#include "System.h"

#include "../AI/aiBlackBoard.h"


class BossSystem : public System
{
public:
	BossSystem() = default;
	~BossSystem() = default;
	void Init() override;
	void Render() override {};
	void Update() override;
	void OnComponentAdd(ENTITY) override;
	void OnComponentRemove(ENTITY) override;

private:
	void CheckOutOfScreen(ENTITY id);
};
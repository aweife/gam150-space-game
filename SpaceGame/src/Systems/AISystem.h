#pragma once

#include "System.h"


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
};
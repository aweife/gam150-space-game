#pragma once

#include "System.h"

class SpaceShipLogicSystem : public System
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void OnComponentAdd(ENTITY entity) override;
	void OnComponentRemove(ENTITY entity) override;
};
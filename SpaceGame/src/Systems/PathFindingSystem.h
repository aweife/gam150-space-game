#pragma once

#include "System.h"

class PathFindingSystem : public System
{
public:
	PathFindingSystem() = default;
	~PathFindingSystem() = default;
	void Init() override;
	void Render() override {};
	void Update() override;
	void OnComponentAdd(ENTITY entity) override;
	void OnComponentRemove(ENTITY entity) override;
};
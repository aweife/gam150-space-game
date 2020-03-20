#pragma once
#include "System.h"
#include <set>
#include "AEVec2.h"

class ProjectileSystem : public System
{
public:
	std::set<ENTITY> objToDestory;
	ProjectileSystem() = default;					//Virtual Constructor...
	~ProjectileSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
	void HomingTarget(AEVec2& targetPos, AEVec2& selfPos, AEVec2& velCurr, AEVec2& steering, float& dirCurr);
};
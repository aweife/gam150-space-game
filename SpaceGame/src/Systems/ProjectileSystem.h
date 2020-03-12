#pragma once
#include "System.h"
#include <set>

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
};
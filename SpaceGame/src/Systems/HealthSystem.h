#pragma once
#include "System.h"
#include <set>
class HealthSystem : public System
{
public:
	std::set<ENTITY> markedForDestruction;

	HealthSystem() = default;					//Virtual Constructor...
	~HealthSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};

	void TakeDamage(ENTITY entity);
};
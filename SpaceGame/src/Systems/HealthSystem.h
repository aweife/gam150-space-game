#pragma once
#include "System.h"

class HealthSystem : public System
{
public:
	HealthSystem() = default;					//Virtual Constructor...
	~HealthSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};
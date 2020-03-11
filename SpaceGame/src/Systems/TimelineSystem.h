#pragma once

#include "System.h"					//Inheritance

class TimelineSystem : public System
{
public:
	TimelineSystem() = default;					//Virtual Constructor...
	~TimelineSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

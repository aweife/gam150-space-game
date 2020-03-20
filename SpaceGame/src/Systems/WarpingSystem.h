#pragma once

#include "System.h"					//Inheritance

class WarpingSystem : public System
{
public:
	WarpingSystem() = default;					//Virtual Constructor...
	~WarpingSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

#pragma once

#include "System.h"					//Inheritance

class WeaponSystemMelee : public System
{
public:
	WeaponSystemMelee() = default;					//Virtual Constructor...
	~WeaponSystemMelee() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

#pragma once

#include "System.h"					//Inheritance
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"
#include "../Components/cWeapon.h"



class WeaponSystemRange : public System
{
public:
	WeaponSystemRange() = default;					//Virtual Constructor...
	~WeaponSystemRange() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};


void NormalShoot(cTransform* transform, OWNERTAG tag);
void HomingShoot(cTransform* transform);
void MachineGunShoot(cTransform* transform);

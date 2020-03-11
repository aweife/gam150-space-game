#pragma once

#include "System.h"					//Inheritance
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"
#include "../Components/cWeapon.h"



class WeaponSystem : public System
{
public:
	WeaponSystem() = default;					//Virtual Constructor...
	~WeaponSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};


void NormalShoot(cTransform* transform);
void HomingShoot(cTransform* transform);
void MachineGunShoot(cTransform* transform);
void EquipWeapon(Weapon* weaponComponent, WeaponType weaponType);
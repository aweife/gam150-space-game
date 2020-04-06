/**********************************************************************************
* \file			UpgradeManager.h
* \brief		Stores all upgrade values for weapon
* \author		Chong Jin Kiat, 100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once
//Hopefully wont have any dependency error here
#include "../Components/cWeapon.h"
#include"../Components/cSpaceShip.h"
#include"../Components/cHealth.h"

const int NUMBER_OF_PLAYERPGRADES = 4;
const int NUMBER_OF_RANGEWEAPONUPGRADES = 7;
const int NUMBER_OF_MELEEWEAPONUPGRADES = 2;
const int NUMBER_OF_UPGRADES_TYPE = 3;

enum class UpgradePackages
{
	PlayerUpgrade_HpUp1,
	PlayerUpgrade_LifeUp1,
	PlayerUpgrade_ShieldUp1,
	PlayerUpgrade_ThrustAccelUp1,

	RangeWeaponUpgrade_FireRateDown1,
	RangeWeaponUpgrade_ReloadRateDown1,
	RangeWeaponUpgrade_AmmoUp1,
	RangeWeaponUpgrade_DamageUp1,
	RangeWeaponUpgrade_SpreadDown1,
	RangeWeaponUpgrade_BulletSizeUp1,
	RangeWeaponUpgrade_BulletSpeedUp1,

	MeleeWeaponUpgrade_RangeUp1,
	MeleeWeaponUpgrade_DamageUp1,
	NONE
};

namespace UpgradeManager
{
	void Init_UpgradeDatabase();
	void Cleanup_UpgradeDatabase();
	const char* GetUpgradeImage(int i);
	int RandomUpgrade();
	void ApplyUpgrade(int upgradeIndex);
	bool CheckUnique(int randomUpgrade);
	void AddActiveUpgrade(int randomUpgrade);
	void ClearAllUpgradeChoice();

	void PlayerUpgrade(cSpaceShip* spaceship, cHealth* health, UpgradePackages upgradePack);
	void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, UpgradePackages upgradePack);
	void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, UpgradePackages upgradePack);
	//void WeaponChange(cRangeWeapon* rangeWeapon, WeaponType weaponType, UpgradePackages upgradePack);
}

//Database of upgrades - BASE CLASS


/******************************** Player Upgrades ********************************/


struct PlayerUpgrade_Base
{
	inline virtual float Get_ThrustAcceleration()	{ return 0.0f; };
	inline virtual float Get_ShieldIncrease()		{ return 0.0f; };
	inline virtual float Get_HealthIncrease()		{ return 0.0f; };
	inline virtual int   Get_LifeIncrease()			{ return 0; };
	//virtual ~PlayerUpgrade_Base() = 0 {};
};

struct PlayerUpgrade_HpUp1: public PlayerUpgrade_Base
{
	inline float Get_HealthIncrease() override		{ return 1.0f; };

};

struct PlayerUpgrade_LifeUp1 : public PlayerUpgrade_Base
{
	inline int Get_LifeIncrease() override { return 1; };

};

struct PlayerUpgrade_ShieldUp1 : public PlayerUpgrade_Base
{
	inline float Get_ShieldIncrease() override { return 1.0f; };

};

struct PlayerUpgrade_ThrustAccelUp1 : public PlayerUpgrade_Base
{
	inline float Get_ThrustAcceleration() override { return 1.0f; };

};
/***************************************************************************************/


/******************************** Range Weapon Upgrades ********************************/

struct WeaponUpgradeRange_BaseRange
{
	inline virtual float Get_FireRateDecrease()			{ return 0.0f; };
	inline virtual float Get_ReloadRateDecrease()		{ return 0.0f; };
	inline virtual int	 Get_AmmoIncrease()				{ return 0;	   };
	inline virtual float Get_DamageIncrease()			{ return 0.0f; };
	inline virtual float Get_SpreadDecrease()			{ return 0.0f; };
	inline virtual float Get_BulletSizeIncrease()		{ return 0.0f; };
	inline virtual float Get_BulletSpeedIncrease()		{ return 0.0f; };
	inline virtual WeaponType Get_WeaponType()			{ return WeaponType::none; };
	//virtual ~WeaponUpgradeRange_BaseRange() = 0 {};
};

struct RangeWeaponUpgrade_FireRateDown1 : public WeaponUpgradeRange_BaseRange
{
	inline float Get_FireRateDecrease() override { return 1.0f; };

};

struct RangeWeaponUpgrade_ReloadRateDown1 : public WeaponUpgradeRange_BaseRange
{
	inline float Get_ReloadRateDecrease() override { return 1.0f; };

};

struct RangeWeaponUpgrade_AmmoUp1 : public WeaponUpgradeRange_BaseRange
{
	inline int Get_AmmoIncrease() override { return 1; };

};

struct RangeWeaponUpgrade_DamageUp1 : public WeaponUpgradeRange_BaseRange
{
	inline float Get_DamageIncrease() override { return 1.0f; };

};

struct RangeWeaponUpgrade_SpreadDown1 : public WeaponUpgradeRange_BaseRange
{
	inline float Get_SpreadDecrease() override { return 1.0f; };

};

struct RangeWeaponUpgrade_BulletSizeUp1 : public WeaponUpgradeRange_BaseRange
{
	inline float Get_BulletSizeIncrease() override { return 1.0f; };

};

struct RangeWeaponUpgrade_BulletSpeedUp1 : public WeaponUpgradeRange_BaseRange
{
	inline float Get_BulletSpeedIncrease() override { return 1.0f; };

};

/***************************************************************************************/


/******************************** Melee Weapon Upgrades ********************************/

struct WeaponUpgradeMelee_BaseMelee
{
	inline virtual float Get_RangeIncrease()  { return 0.0f; };
	inline virtual float Get_DamageIncrease()  { return 0.0f; };

	//virtual ~WeaponUpgradeMelee_BaseMelee() = 0 {};
};

struct MeleeWeaponUpgrade_RangeUp1 : public WeaponUpgradeMelee_BaseMelee
{
	inline float Get_RangeIncrease() override { return 1.0f; };

};

struct MeleeWeaponUpgrade_DamageUp1 : public WeaponUpgradeMelee_BaseMelee
{
	inline float Get_DamageIncrease() override { return 1.0f; };

};

/***************************************************************************************/





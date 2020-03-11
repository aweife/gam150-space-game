#pragma once
//Hopefully wont have any dependency erro here
#include "../Components/cWeapon.h"
#include"../Components/cSpaceShip.h"
#include"../Components/cHealth.h"

enum class UpgradePackages
{
	Player_V1,
	Range_Pistol,
	Melee_Normal
};

namespace UpgradeManager
{
	void Init_UpgradeDatabase();
	void Cleanup_UpgradeDatabase();

	void PlayerUpgrade(cSpaceShip* spaceship, cHealth* health, UpgradePackages upgradePack, int level);
	void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, UpgradePackages upgradePack, int level);
	void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, UpgradePackages upgradePack, int level);
	void WeaponChange(cRangeWeapon* rangeWeapon, WeaponType weaponType, UpgradePackages upgradePack);
}

//Database of upgrades - BASE CLASS

struct PlayerUpgrade_Base
{
	inline virtual float Get_U0_ThrustDelay() = 0;
	inline virtual float Get_U0_ShootDelay() = 0;
	inline virtual float Get_U0_Shield() = 0;
	inline virtual float Get_U0_Health() = 0;
	inline virtual int   Get_U0_Life() = 0;

	inline virtual float Get_U1_ThrustDelay() = 0;
	inline virtual float Get_U1_ShootDelay() = 0;
	inline virtual float Get_U1_ShieldIncrease() = 0;
	inline virtual float Get_U1_HealthIncrease() = 0;
	inline virtual int   Get_U1_LifeIncrease() = 0;

	inline virtual float Get_U2_ThrustDelay() = 0;
	inline virtual float Get_U2_ShootDelay() = 0;
	inline virtual float Get_U2_ShieldIncrease() = 0;
	inline virtual float Get_U2_HealthIncrease() = 0;
	inline virtual int	 Get_U2_LifeIncrease() = 0;
};

struct PlayerUpgrade_V1: public PlayerUpgrade_Base
{
	/******************************** Player Upgrades ********************************/
	/******** Player Upgrade Level 0 ********/
	inline float Get_U0_ThrustDelay()		{ return 0.5f; };
	inline float Get_U0_ShootDelay()		{ return 0.5f; };
	/****************************************/

	/******** Player Upgrade Level 1 ********/
	inline float Get_U1_ThrustDelay()		{ return 0.5f; };
	inline float Get_U1_ShootDelay()		{ return 0.5f; };
	/****************************************/

	/******** Player Upgrade Level 2 ********/
	inline float Get_U2_ThrustDelay()		{ return 1.0f; };
	inline float Get_U2_ShootDelay()		{ return 1.0f; };
	/****************************************/


	////////////////////////////////////////////////////////////////////////////////////


	/******************************** Health & Shield Upgrades ********************************/
	/******** Health Upgrade Level 0 ********/
	inline float Get_U0_Shield()			{ return 60.0f; }
	inline float Get_U0_Health()			{ return 100.0f; }
	inline int   Get_U0_Life()				{ return 3; }
	/****************************************/


	/******** Health Upgrade Level 1 ********/
	inline float Get_U1_ShieldIncrease()	{ return 10.0f; }
	inline float Get_U1_HealthIncrease()	{ return 20.0f; }
	inline int   Get_U1_LifeIncrease()		{ return 1;		}
	/****************************************/


	/******** Health Upgrade Level 2 ********/
	inline float Get_U2_ShieldIncrease()	{ return 50.0f; }
	inline float Get_U2_HealthIncrease()	{ return 50.0f; }
	inline int   Get_U2_LifeIncrease()		{ return 2;		}
	/***************************************/

	////////////////////////////////////////////////////////////////////////////////////

};

struct WeaponUpgrade_BaseRange
{
	inline virtual float Get_U0_FireRate() = 0;
	inline virtual float Get_U0_ReloadRate() = 0;
	inline virtual int	 Get_U0_Ammo() = 0;
	inline virtual float Get_U0_Damage() = 0;

	inline virtual float Get_U1_FireRate() = 0;
	inline virtual float Get_U1_ReloadRate() = 0;
	inline virtual int	 Get_U1_Ammo() = 0;
	inline virtual float Get_U1_Damage() = 0;

	inline virtual float Get_U2_FireRate() = 0;
	inline virtual float Get_U2_ReloadRate() = 0;
	inline virtual int	 Get_U2_Ammo() = 0;
	inline virtual float Get_U2_Damage() = 0;
};

struct WeaponUpgrade_Pistol: public WeaponUpgrade_BaseRange
{
	/******************************** Weapon Upgrades ********************************/
	/******** Range Weapon Upgrade Level 0 ********/
	inline float Get_U0_FireRate()			{ return 10.0f; };
	inline float Get_U0_ReloadRate()		{ return 20.0f; };
	inline int	 Get_U0_Ammo()				{ return 10; };
	inline float Get_U0_Damage()			{ return 20.0f; };
	/*************************************************/

	/******** Range Weapon Upgrade Level 1 ********/
	inline float Get_U1_FireRate()			{ return 10.0f; };
	inline float Get_U1_ReloadRate()		{ return 20.0f; };
	inline int	 Get_U1_Ammo()				{ return 10; };
	inline float Get_U1_Damage()			{ return 20.0f; };
	/*************************************************/

	/******** Range Weapon Upgrade Level 2 ********/
	inline float Get_U2_FireRate()			{ return 10.0f; };
	inline float Get_U2_ReloadRate()		{ return 20.0f; };
	inline int	 Get_U2_Ammo()				{ return 10; };
	inline float Get_U2_Damage()			{ return 20.0f; };
	/*************************************************/

	////////////////////////////////////////////////////////////////////////////////////
};

struct WeaponUpgrade_BaseMelee
{
	inline virtual float Get_U0_MeleeRange() = 0;
	inline virtual float Get_U0_Damage() = 0;

	inline virtual float Get_U1_MeleeRange() = 0;
	inline virtual float Get_U1_Damage() = 0;
};

struct WeaponUpgrade_Normal: public WeaponUpgrade_BaseMelee
{
	/******** Melee Weapon Upgrade Level 0********/
	inline float Get_U0_MeleeRange()		{ return 40.0f; };
	inline float Get_U0_Damage()			{ return 50.0f; };
	/*********************************************/

	/******** Melee Weapon Upgrade Level 1********/
	inline float Get_U1_MeleeRange()		{ return 50.0f; };
	inline float Get_U1_Damage()			{ return 60.0f; };
	/*********************************************/
};






#pragma once
#include "../Components/cWeapon.h"
#include"../Components/cSpaceShip.h"
#include"../Components/cHealth.h"

struct PlayerUpgrade
{
	/******************************** Player Upgrades ********************************/
	/******** Player Upgrade Level 1 ********/
	float U1_thrustDelay = 0.5f;
	float U1_shootDelay = 0.5f;
	/*************************************/


	/******** Player Upgrade Level 2 ********/
	float U2_thrustDelay = 1.0f;
	float U2_shootDelay = 1.0f;
	/*************************************/


	////////////////////////////////////////////////////////////////////////////////////


	/******************************** Health & Shield Upgrades ********************************/

	/******** Health Upgrade Level 1 ********/
	float U1_shieldIncrease = 10.0f;
	float U1_healthIncrease = 20.0f;
	/*************************************/


	/******** Health Upgrade Level 2 ********/
	float U2_shieldIncrease = 50.0f;
	float U2_healthIncrease = 50.0f;
	/***************************************/

	////////////////////////////////////////////////////////////////////////////////////



	/******************************** Weapon Upgrades ********************************/

	/******** Range Weapon Upgrade Level 1 ********/
	float U1_fireRate = 10.0f;
	float U1_reloadRate = 20.0f;
	/*************************************/

	/******** Range Weapon Upgrade Level 1 V2 ********/
	int U1_ammo = 10;
	float U1_damage = 20.0f;
	/*************************************/


	/******** Melee Weapon Upgrade Level 1********/
	float U1_meleeRange = 50.0f;
	float U1_damage = 50.0f;
	/***************************************/

	////////////////////////////////////////////////////////////////////////////////////


};

void PlayerUprade(cSpaceShip* spaceship, float thrustDelay, int lives);
void PlayerHealthUpgrade(cHealth* health, float shieldIncrease, float healthIncrease);
void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, float fireRate, float reloadRate, int ammo, float damage);
void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, float meleeRanage, float damage);
void WeaponChange(cRangeWeapon* rangeWeapon, cRangeWeapon* weaponType);

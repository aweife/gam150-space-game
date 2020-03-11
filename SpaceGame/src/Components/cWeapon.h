/**********************************************************************************
* \file			cSpaceShip.h
* \brief		Component for range and melee weapons
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Enum to classify weapon type
*				- Derived class from a base weapon class
*				- Data for range or melee weapon component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"

enum class WeaponType
{
	none,
	pistol,
	machineGun,
	tripleShot,
	grenadeGun,
	laser,
	melee					//Only one melee for now
};

class Weapon				//Pure Virtual Class
{
public:
	WeaponType	_currWeapon;
	float		_damage;

	virtual ~Weapon() = 0 {};
};

class cRangeWeapon: public Weapon, Component
{
public:
	bool		_isShooting;			//Player input
	float		_fireRate;
	float		_reloadRate;
	bool		_isReloading;
	bool		_isFiring;				//?????
	int			_ammo;					//ammo count

	cRangeWeapon() = default;
	cRangeWeapon(bool isShooting, float fireRate, float reloadRate, bool isReloading, bool isFiring, int ammo);
	~cRangeWeapon() {};
};

class cMeleeWeapon : public Weapon, Component
{
public:
	float		_meleeRange;			

	cMeleeWeapon() = default;
	cMeleeWeapon(float meleeRange);
	~cMeleeWeapon() {};
};
/**********************************************************************************
* \file			cWeapon.h
* \brief		Weapon
* \author		Jin Kiat,		Chong,  100% Code Contribution
*
*				Handles the Weapon component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"
#include "cRigidBody.h"

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
	WeaponType	_currWeapon		= WeaponType::none;
	float		_damage			= 0.0f;

	virtual ~Weapon() = 0 {};
};


class cRangeWeapon : public Weapon, public Component
{
public:
	bool		_playerIsShooting;		//Player input
	bool		_enemyIsShooting;			

	float		_fireCooldownTimer;
	float		_fireCooldown;
	float		_reloadRate;
	bool		_isReloading;
	int			_ammo;					//ammo count
	float		_shootingSpread;
	float		_bulletSize;
	float		_bulletSpeed;
	float		_chargeTime;

	ENTITY	_permenanceProjectile = 0;

	// Temporary
	float	_attackCooldown;
	float	_attackCooldownTimer;
	int		_attacksLeft;
	float	_delayTimer;
	float	_delayBetweenAttacks;
	int		_numberOfAttacks;

	// Boss
	bool	_bossIsShooting;
	AEVec2	_targetPosition;
	bool	_homing;

	OWNERTAG _tag;

	cRangeWeapon() = default;
	cRangeWeapon(OWNERTAG tag, WeaponType weaponType, float attackCooldown, float delayBetweenAttacks = 0.0f, int numberOfAttacks = 1);
	cRangeWeapon(bool isShooting, float currFireRate, float reloadRate, int ammo, float shootingSpread
		, float bulletSize, float bulletSpeed, float chargeTime);
	~cRangeWeapon() {};
};

class cMeleeWeapon : public Weapon, public Component
{
public:
	float		_meleeRange;

	cMeleeWeapon() = default;
	cMeleeWeapon(float meleeRange);
	~cMeleeWeapon() {};
};
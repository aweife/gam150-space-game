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
	melee
};

class Weapon
{
public:
	WeaponType _currWeapon;
	float _damage;

	virtual ~Weapon() = 0 {};
};

class cRangeWeapon: public Weapon, Component
{
public:
	bool _isShooting;
	float _fireRate;
	float _reloadRate;
	bool _isReloading;
	bool _isFiring;
	int _ammo;

	cRangeWeapon() = default;
	cRangeWeapon(bool isShooting, float fireRate, float reloadRate, bool isReloading, bool isFiring, int ammo);
	~cRangeWeapon() {};
};

class cMeleeWeapon : public Weapon, Component
{
public:
	float _meleeRange;

	cMeleeWeapon() = default;
	cMeleeWeapon(float meleeRange);
	~cMeleeWeapon() {};
};
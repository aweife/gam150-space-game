#include "UpgradeManager.h"

void PlayerUprade(cSpaceShip* spaceship, float thrustDelay, int lives)
{
	spaceship->_thrustDelay -= thrustDelay;
	spaceship->_lives += lives;
}

void PlayerHealthUpgrade(cHealth* health, float shieldIncrease, float healthIncrease)
{
	health->_healthMax += healthIncrease;
	health->_shieldMax += shieldIncrease;
}

void WeaponUpgradeRange(cRangeWeapon* rangeWeapon, float fireRate, float reloadRate, int ammo, float damage)
{
	rangeWeapon->_fireRate -= fireRate;
	rangeWeapon->_reloadRate -= reloadRate;
	rangeWeapon->_ammo += ammo;
	rangeWeapon->_damage += damage;
}

void WeaponUpgradeMelee(cMeleeWeapon* meleeWeapon, float meleeRange, float damage)
{
	meleeWeapon->_meleeRange -= meleeRange;
	meleeWeapon->_damage += damage;
}

void WeaponChange(cRangeWeapon* rangeWeapon, cRangeWeapon* weaponType)
{
	rangeWeapon->_currWeapon = weaponType;
}


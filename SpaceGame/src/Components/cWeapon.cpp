#include "cWeapon.h"



cRangeWeapon::cRangeWeapon(bool isShooting, float fireRate, float reloadRate, bool isReloading, bool isFiring, int ammo)
	: _isShooting{isShooting},
	_fireRate{ fireRate },
	_reloadRate{ reloadRate },
	_isReloading{ isReloading },
	_isFiring{ isFiring },
	_ammo{ ammo }
{

}

cMeleeWeapon::cMeleeWeapon(float meleeRange)
	:_meleeRange{meleeRange}
{

}

#include "cWeapon.h"



cRangeWeapon::cRangeWeapon(bool isShooting, float fireRate, float currFireRate, float reloadRate, bool isReloading, bool isFiring, int ammo,
	float shootingSpread, float bulletSize, float bulletSpeed):
	_isShooting{ isShooting },
	_fireRate{ fireRate },
	_currfireRate{ currFireRate },
	_reloadRate{ reloadRate },
	_isReloading{ isReloading },
	_isFiring{ isFiring },
	_ammo{ ammo },
	_shootingSpread{shootingSpread},
	_bulletSize{ bulletSize },
	_bulletSpeed{bulletSpeed}
{

}

cMeleeWeapon::cMeleeWeapon(float meleeRange)
	:_meleeRange{meleeRange}
{

}

#include "cWeapon.h"



cRangeWeapon::cRangeWeapon(float fireRate, float currFireRate, float reloadRate, int ammo,
	float shootingSpread, float bulletSize, float bulletSpeed, float chargeTime):
	_isShooting{ false },
	_fireRate{ fireRate },
	_currfireRate{ currFireRate },
	_reloadRate{ reloadRate },
	_isReloading{ false},
	_ammo{ ammo },
	_shootingSpread{shootingSpread},
	_bulletSize{ bulletSize },
	_bulletSpeed{bulletSpeed},
	_chargeTime{ chargeTime }
{

}

cMeleeWeapon::cMeleeWeapon(float meleeRange)
	:_meleeRange{meleeRange}
{

}

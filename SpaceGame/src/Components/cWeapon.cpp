#include "cWeapon.h"



cRangeWeapon::cRangeWeapon(float attackCooldown, float delayBetweenAttacks, int numberOfAttacks) :
	_isShooting{ false },
	_attackCooldown{ attackCooldown },
	_delayBetweenAttacks{ delayBetweenAttacks },
	_numberOfAttacks{ numberOfAttacks },
	_attackCooldownTimer{ 0.0f },
	_attacksLeft{ 0 },
	_delayTimer{ 0.0f } {}

cRangeWeapon::cRangeWeapon(bool isShooting, float currFireRate, float reloadRate, bool isReloading, bool isFiring, int ammo,
	float shootingSpread, float bulletSize, float bulletSpeed) :
	_isShooting{ isShooting },
	_fireCooldownTimer{ 0.0f },
	_fireCooldown{ currFireRate },
	_reloadRate{ reloadRate },
	_isReloading{ isReloading },
	_isFiring{ isFiring },
	_ammo{ ammo },
	_shootingSpread{ shootingSpread },
	_bulletSize{ bulletSize },
	_bulletSpeed{ bulletSpeed } {}

cMeleeWeapon::cMeleeWeapon(float meleeRange)
	:_meleeRange{ meleeRange } {}

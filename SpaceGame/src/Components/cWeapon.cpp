#include "cWeapon.h"

cRangeWeapon::cRangeWeapon(OWNERTAG tag, float attackCooldown, float delayBetweenAttacks, int numberOfAttacks) :
	_playerIsShooting{ false },
	_enemyIsShooting{ false },
	_attackCooldown{ attackCooldown },
	_delayBetweenAttacks{ delayBetweenAttacks },
	_numberOfAttacks{ numberOfAttacks },
	_attackCooldownTimer{ 0.0f },
	_attacksLeft{ 0 },
	_delayTimer{ 0.0f },
	_tag{ tag },
	_ammo{ numberOfAttacks },

	// Uninitalised
	
	_bulletSize{ 0.0f },
	_bulletSpeed{ 0.0f },
	_chargeTime{ 0.0f },
	_fireCooldownTimer{ 0.0f },
	_fireCooldown{ 0.0f },
	_reloadRate{ 0.0f },
	_isReloading{ false },
	_shootingSpread{ 0.0f },
	_bossIsShooting{ false }
{
	_currWeapon = weaponType;
}


cRangeWeapon::cRangeWeapon(bool isShooting, float currFireRate, float reloadRate, int ammo,
	float shootingSpread, float bulletSize, float bulletSpeed, float chargeTime) :
	_enemyIsShooting{ isShooting },
	_fireCooldownTimer{ 0.0f },
	_fireCooldown{ currFireRate },
	_reloadRate{ reloadRate },
	_isReloading{ false },
	_ammo{ ammo },
	_shootingSpread{ shootingSpread },
	_bulletSize{ bulletSize },
	_bulletSpeed{ bulletSpeed },
	_chargeTime{ chargeTime },

	//AI STUFF
	_attackCooldown{ 0.0f },
	_delayBetweenAttacks{ 0.0f },
	_numberOfAttacks{ 0 },
	_attackCooldownTimer{ 0.0f },
	_attacksLeft{ 0 },
	_delayTimer{ 0.0f },
	_tag{ OWNERTAG::PLAYER }
{

}

cMeleeWeapon::cMeleeWeapon(float meleeRange)
	:_meleeRange{ meleeRange } {}

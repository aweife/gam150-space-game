#include "cProjectile.h"

cProjectile::cProjectile(float bulletLifeTime, float currBulletLifeTime, bulletType bulletType, bool homing)
	:_bulletLifeTime{bulletLifeTime},
	_currBulletLifeTime{currBulletLifeTime},
	_bulletType{bulletType},
	_homing{homing}
{

}
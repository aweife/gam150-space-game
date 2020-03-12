#include "cProjectile.h"

cProjectile::cProjectile(float bulletLifeTime, float currBulletLifeTime, bulletType bulletType)
	:_bulletLifeTime{bulletLifeTime},
	_currBulletLifeTime{currBulletLifeTime},
	_bulletType{bulletType}
{

}
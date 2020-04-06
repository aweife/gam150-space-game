/**********************************************************************************
* \file			cProjectile.cpp
* \brief		Projectile
* \author		Wei Feng,				Ang,  100% Code Contribution
*
*				Handles the projectile component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cProjectile.h"

cProjectile::cProjectile(float bulletLifeTime, float currBulletLifeTime, bulletType bulletType, bool homing)
	:_bulletLifeTime{bulletLifeTime},
	_currBulletLifeTime{currBulletLifeTime},
	_bulletType{bulletType},
	_homing{homing}
{

}
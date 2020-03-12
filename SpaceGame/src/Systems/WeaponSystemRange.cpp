#include "WeaponSystemRange.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"
#include <iostream>

#include "../ECS/Factory.h"
/******************************************************************************/
/*!
	Global Variables
*/
/******************************************************************************/

void WeaponSystemRange::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRangeWeapon>());
	signature.set(Core::Get().GetComponentType<cSpaceShip>());
	Core::Get().SetSystemSignature<WeaponSystemRange>(signature);
}

void WeaponSystemRange::Update()
{
	cTransform* transform;
	cRangeWeapon* rangeweapon;
	cSpaceShip* spaceship;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rangeweapon = Core::Get().GetComponent<cRangeWeapon>(entity);
		spaceship = Core::Get().GetComponent<cSpaceShip>(entity);

		//Time update
		if (rangeweapon->_isShooting)
		{
			rangeweapon->_fireRate -= g_dt;

			if (rangeweapon->_fireRate <= 0)
			{
				rangeweapon->_fireRate = rangeweapon->_currfireRate;
			}

			//if (/*spaceship->_currWeaponMode == WeaponMode::range &&*/
			//	rangeweapon->_isShooting /*&& spaceship->_shootDelay > rangeweapon->_fireRate*/)
			//{
			//	switch (rangeweapon->_currWeapon)
			//	{
			//	case WeaponType::pistol:
			//		rangeweapon->_fireRate = 0.0f;
			//		NormalShoot(transform);
			//		break;
			//	case WeaponType::machineGun:
			//		rangeweapon->_fireRate = 0.0f;
			//		MachineGunShoot(transform);
			//		break;
			//	case WeaponType::grenadeGun:
			//		break;
			//	case WeaponType::laser:
			//		break;
			//	}
			//}
		}
	}
}

void NormalShoot(cTransform* transform)
{
	AEVec2 bulletDirection;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
	// Spawn the bullet at the tip of player
	Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * 100.0f,
		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, bulletDirection, transform->_rotation + PI / 2);
}

void HomingShoot(cTransform* transform)
{
	(void)transform;
}

void MachineGunShoot(cTransform* transform)
{
	AEVec2 bulletDirection;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
	// Spawn the bullet at the tip of player
	Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * 100.0f,
		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, bulletDirection, transform->_rotation + PI / 2);
}

//void TripleShot(cTransform* transform)
//{
//	AEVec2 bulletDirection;
//	AEVec2 bulletVelocity;
//
//	// Setting the direction of bullet spawn
//	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
//	// Bullet velocity
//	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
//	// Spawn the bullet at the tip of player
//	Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * 100.0f,
//		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, transform->_rotation + PI / 2);
//}

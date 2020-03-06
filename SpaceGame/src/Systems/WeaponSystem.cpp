#include "WeaponSystem.h"
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

void WeaponSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cRangeWeapon>());
	signature.set(Core::Get().GetComponentType<cMeleeWeapon>());
	signature.set(Core::Get().GetComponentType<cSpaceShip>());
	Core::Get().SetSystemSignature<WeaponSystem>(signature);
}

void WeaponSystem::Update()
{
	cTransform* transform;
	cRigidBody* rigidbody;
	cSpaceShip* spaceship;
	cRangeWeapon* rangeweapon;
	cMeleeWeapon* meleeweapon;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity);
		spaceship = Core::Get().GetComponent<cSpaceShip>(entity);
		rangeweapon = Core::Get().GetComponent<cRangeWeapon>(entity);
		meleeweapon = Core::Get().GetComponent<cMeleeWeapon>(entity);

		//Time update
		rangeweapon->_fireRate += g_dt;

		if (/*spaceship->_currWeaponMode == WeaponMode::range &&*/ rangeweapon->_isShooting /*&& spaceship->_shootDelay > rangeweapon->_fireRate*/)
		{

			std::cout << "shootpistol" << std::endl;
			switch (rangeweapon->_currWeapon)
			{
			case WeaponType::pistol:
				rangeweapon->_fireRate = 0.0f;
				NormalShoot(transform);
				break;
			case WeaponType::machineGun:
				rangeweapon->_fireRate = 0.0f;
				MachineGunShoot(transform);
				break;
			case WeaponType::grenadeGun:
				break;
			case WeaponType::laser:
				break;
			}
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
		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, transform->_rotation + PI / 2);
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
		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, transform->_rotation + PI / 2);
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

void EquipWeapon(Weapon* weaponComponent, WeaponType weaponType)
{
	weaponComponent->_currWeapon = weaponType;
}
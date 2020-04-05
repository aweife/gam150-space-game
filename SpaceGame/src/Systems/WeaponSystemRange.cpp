/*********************************************************************************
* \file			WeaponSystemRange.cpp
* \brief		Controls the range weapon of every entities
* \author		Chong Jin Kiat, 75% Code Contribution
* \author		Ang Wei Feng, 25% Code Contribution
*
*				This system loops through all its components in the game and make
*				sure they fire at their respective speed and delays
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "WeaponSystemRange.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"
#include <iostream>
#include "../Tools/Editor.h"

#include "../ECS/Factory.h"
#include "../Player/PlayerManager.h"
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
	Core::Get().SetSystemSignature<WeaponSystemRange>(signature);
}

void WeaponSystemRange::Update()
{
	cTransform* transform;
	cRangeWeapon* rangeweapon;

	const ENTITY pid = PlayerManager::player;
	if (pid == 0)	return;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rangeweapon = Core::Get().GetComponent<cRangeWeapon>(entity);

		if (!rangeweapon->_playerIsShooting)
		{
			if (rangeweapon->_currWeapon == WeaponType::laser && rangeweapon->_permenanceProjectile)
			{
				Core::Get().EntityDestroyed(rangeweapon->_permenanceProjectile);
				rangeweapon->_permenanceProjectile = 0;
				rangeweapon->_ammo = 1;
			}
			//continue;
		}

		// ENEMY
		if (rangeweapon->_enemyIsShooting)
		{
			if (rangeweapon->_attackCooldownTimer > 0.0f)
			{
				rangeweapon->_attackCooldownTimer -= g_dt;

				if (rangeweapon->_attacksLeft > 0)
				{
					// Currently attacking, set delay between attacks
					if (rangeweapon->_delayTimer > 0.0f)
						rangeweapon->_delayTimer -= g_dt;
					else
					{
						// Set delay
						rangeweapon->_delayTimer = rangeweapon->_delayBetweenAttacks;

						// Fire
						if (rangeweapon->_bossIsShooting)
						{
							if (rangeweapon->_homing)
								HomingShoot(transform, rangeweapon->_tag, PlayerManager::player);
							else
								TargetShoot(transform, rangeweapon->_tag, rangeweapon->_targetPosition);
						}
						else
						{
							StraightShoot(transform, rangeweapon->_tag);
							--rangeweapon->_attacksLeft;
						}
					}
				}
				else
					rangeweapon->_enemyIsShooting = false;
			}
			else
			{
				// Set cooldown
				rangeweapon->_attackCooldownTimer = rangeweapon->_attackCooldown;
				rangeweapon->_attacksLeft = rangeweapon->_numberOfAttacks;
			}
		}
		else
		{
			// PLAYER
			if (rangeweapon->_playerIsShooting)
			{
				if (rangeweapon->_delayTimer > 0.0f)
					rangeweapon->_delayTimer -= g_dt;
				else
				{
					rangeweapon->_delayTimer = rangeweapon->_delayBetweenAttacks;
					ChooseShootingStyle(rangeweapon, transform);
				}
			}
			else
				rangeweapon->_delayTimer = 0.0f;
		}
	}
}

void ChooseShootingStyle(cRangeWeapon* rangeWeapComp, cTransform* transformComp)
{
	switch (rangeWeapComp->_currWeapon)
	{
	case WeaponType::pistol:
		StraightShoot(transformComp, rangeWeapComp->_tag);
		--rangeWeapComp->_attacksLeft;
		rangeWeapComp->_playerIsShooting = false;
		break;
	case WeaponType::laser:
		LaserBeam(transformComp, rangeWeapComp);
		rangeWeapComp->_ammo = 0;
		break;

	}
}

void StraightShoot(cTransform* transform, OWNERTAG tag)
{
	AEVec2 bulletDirection;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);

	// Spawn the bullet at the tip of player
	if (tag == OWNERTAG::PLAYER)
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * (transform->_scale.x / 2.0f),
			transform->_position.y + AESin(transform->_rotation) * (transform->_scale.y / 2.0f), bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::PLAYER);
	else if (tag == OWNERTAG::AI)
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * (transform->_scale.x / 2.0f),
			transform->_position.y + AESin(transform->_rotation) * (transform->_scale.y / 2.0f), bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::AI);
}

void TargetShoot(cTransform* transform, OWNERTAG tag, AEVec2& targetPos)
{
	AEVec2 bulletDirection;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Sub(&bulletDirection, &targetPos, &transform->_position);
	AEVec2Normalize(&bulletDirection, &bulletDirection);
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);

	Factory::CreateBullet(transform->_position.x,
		transform->_position.y, bulletVelocity, bulletDirection, atan2f(bulletDirection.y, bulletDirection.x) + PI / 2, OWNERTAG::AI);
}

void HomingShoot(cTransform* transform, OWNERTAG tag, ENTITY target)
{
	AEVec2 bulletDirection = Core::Get().GetComponent<cTransform>(target)->_position;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Sub(&bulletDirection, &bulletDirection, &transform->_position);
	AEVec2Normalize(&bulletDirection, &bulletDirection);
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 300.0f);

	Factory::CreateHomingMissile(transform->_position.x,
		transform->_position.y, bulletVelocity, bulletDirection, atan2f(bulletDirection.y, bulletDirection.x) + PI / 2, OWNERTAG::AI, target);
}

void MultiShot(cTransform* transform)
{
	(void)transform;
}

void LaserBeam(cTransform* transform, cRangeWeapon* rangeWeapComp)
{
	AEVec2 offset;
	AEVec2Set(&offset, transform->_position.x + AECos(transform->_rotation) * transform->_scale.x / 2, transform->_position.y + AESin(transform->_rotation) * transform->_scale.y / 2);
	if (rangeWeapComp->_ammo)
	{
		rangeWeapComp->_permenanceProjectile = Factory::CreateBullet_LaserBeam(offset.x, offset.y
			, transform->_rotation, rangeWeapComp->_tag);
	}

	if (rangeWeapComp->_permenanceProjectile)
	{
		cTransform* laserTransform = Core::Get().GetComponent<cTransform>(rangeWeapComp->_permenanceProjectile);
		laserTransform->_position = offset;
		laserTransform->_rotation = transform->_rotation;
	}


}

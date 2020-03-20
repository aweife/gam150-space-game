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
	Core::Get().SetSystemSignature<WeaponSystemRange>(signature);
}

void WeaponSystemRange::Update()
{
	cTransform* transform;
	cRangeWeapon* rangeweapon;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rangeweapon = Core::Get().GetComponent<cRangeWeapon>(entity);

		if (!rangeweapon->_isShooting)
		{
			if (rangeweapon->_currWeapon == WeaponType::laser && rangeweapon->_permenanceProjectile)
			{
				Core::Get().EntityDestroyed(rangeweapon->_permenanceProjectile);
				rangeweapon->_permenanceProjectile = 0;
				rangeweapon->_ammo = 1;
			}
			continue;
		}


		//JY - i dont understand..
		// Decrement timer if on cooldown
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
					ChooseShootingStyle(rangeweapon, transform);
					
				}
			}
		}
		else
		{
			// Set cooldown
			rangeweapon->_attackCooldownTimer = rangeweapon->_attackCooldown;
			rangeweapon->_attacksLeft = rangeweapon->_numberOfAttacks;
			rangeweapon->_ammo = rangeweapon->_numberOfAttacks;
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
			rangeWeapComp->_isShooting = false;
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
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * (transform->_scale.x/2.0f),
			transform->_position.y + AESin(transform->_rotation) * (transform->_scale.y/2.0f), bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::PLAYER);
	else if (tag == OWNERTAG::AI)
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * (transform->_scale.x / 2.0f),
			transform->_position.y + AESin(transform->_rotation) * (transform->_scale.y / 2.0f), bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::AI);
}

void HomingShoot(cTransform* transform)
{
	(void)transform;
}


void MultiShot(cTransform* transform)
{

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
		cSprite* laserSprite = Core::Get().GetComponent<cSprite>(rangeWeapComp->_permenanceProjectile);
		laserTransform->_position = offset;
		laserTransform->_rotation = transform->_rotation;
		//laserSprite->_UVOffset.x = 0.5 + ;
	}


}

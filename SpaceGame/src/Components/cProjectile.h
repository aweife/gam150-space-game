/**********************************************************************************
* \file			cProjectile.h
* \brief		Projectile
* \author		Wei Feng,				Ang,  100% Code Contribution
*
*				Handles the projectile component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"
#include "AEVec2.h"
#include "../Global_ECS.h"

enum class bulletType
{
	normal,
	laser
};

class cProjectile:public Component
{
public:
	float _bulletLifeTime;
	float _currBulletLifeTime;

	bool _homing;
	ENTITY _targetId;


	bulletType _bulletType = bulletType::normal;

	cProjectile() = delete;
	cProjectile(float bulletLifeTime, float currBulletLifeTime, bulletType bulletType, bool homing = false);
	~cProjectile() = default;

};
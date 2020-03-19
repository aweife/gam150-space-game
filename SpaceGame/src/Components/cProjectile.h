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
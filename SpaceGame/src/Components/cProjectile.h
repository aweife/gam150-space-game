#pragma once
#include "Component.h"

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

	bulletType _bulletType = bulletType::normal;

	cProjectile() = delete;
	cProjectile(float bulletLifeTime, float currBulletLifeTime, bulletType bulletType);
	~cProjectile() = default;

};
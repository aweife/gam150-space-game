/**********************************************************************************
* \file			cSpaceShip.h
* \brief		Component for interlligent entity that behave like spaceship
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Data for thrust movement
*				- Data for weapon capability
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"

enum class WeaponMode
{
	none,					//If the spaceship does not have weapon features
	range,
	melee
};

class cSpaceShip:public Component
{
public:
	// Spaceship Thruster (Movements)
	bool	_isThrusting;			// Check for thruster use from player/AI input
	float	_thrustDelay;			// Countdown timer when thruster overheats
	float	_thrustAcceleration;	// ????? need to double comfirm

	int		_lives;					// 
	
	WeaponMode _currWeaponMode = WeaponMode::range;	//We can know if the spaceship has any weapon features

	cSpaceShip() = delete;
	cSpaceShip(bool isThrusting, float thrustDelay, int lives, WeaponMode currWeaponMode);
	~cSpaceShip() = default;
};
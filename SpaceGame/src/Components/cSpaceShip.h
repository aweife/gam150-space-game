#pragma once
/*********************************************************************************
* \file			cSpaceShip.h
* \author		Chong Jin Kiat
* \version		1.0
* \date			31/01/2020
* \par			Systems
* \note			Course: GAM150
* \brief		Component for Player Spaceship and AI Spaceship
				- Thruster
				- Shield
				- Timer

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Component.h"

class cSpaceShip:public Component
{
public:
	bool	_isThrusting;			// Check for thruster use
	float	_thrustDelay;			// Countdown timer
	float	_shield;				// Shield amount
	bool	_activateShield;		// Check for shield activation
	int		_lives;					// ok
	float	_health;
	bool	_isShooting;
	float	_shootDelay;

	cSpaceShip();
	~cSpaceShip() = default;
};
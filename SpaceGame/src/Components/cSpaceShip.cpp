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

#include "cSpaceShip.h"

bool isThrusting = false; // Set to default false 
float thrustDelay = 3.0f; // Set to default value
bool activateShield = false; // Set to default false
float shield = 50.0f; // Set to default value
int lives = 3; //ok
float health = 100.0f;
bool isShooting = false;
float shootDelay = 0.0f;


cSpaceShip::cSpaceShip() :
	_isThrusting{ isThrusting }, _thrustDelay{ thrustDelay },
	_activateShield{ activateShield }, _shield{ shield },
	_lives{ lives }, _health{ health },
	_isShooting{ isShooting }, _shootDelay{ shootDelay }
{

}


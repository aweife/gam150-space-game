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


cSpaceShip::cSpaceShip(bool isThrusting, float thrustDelay, int lives, float thrustSpeedAddition, WeaponMode currWeaponMode)
	:_isThrusting{ isThrusting }, 
	_thrustDelay{ thrustDelay },
	_lives{ lives },
	_thrustSpeedAddition{thrustSpeedAddition},
	_currWeaponMode{currWeaponMode}
{

}


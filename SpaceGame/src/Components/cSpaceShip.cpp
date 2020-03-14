/**********************************************************************************
* \file			cSpaceShip.h
* \brief		Component for interlligent entity that behave like spaceship
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Constructor definition for component data
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cSpaceShip.h"		//Component class declaration


cSpaceShip::cSpaceShip(bool isThrusting, float thrustDelay, WeaponMode currWeaponMode) :
	_isThrusting{ isThrusting },
	_thrustDelay{ thrustDelay },
	_currWeaponMode{ currWeaponMode }{}


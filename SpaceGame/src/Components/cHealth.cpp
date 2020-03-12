/**********************************************************************************
* \file			cHealth.cpp
* \brief		Component for entity that have health/shield and can die
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Constructor for component data
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cHealth.h"				//component class declaration

cHealth::cHealth(int shieldMax, int healthMax,float shieldRegenCooldown, float invulnerabilityWindow) :
	_activateShield{ true },
	_shieldMax{ shieldMax },
	_healthMax{ healthMax },
	_shieldCurr{ _shieldMax },
	_healthCurr{ _healthMax },
	_shieldRegenCooldown{ shieldRegenCooldown },
	_shieldRegenTimer{ 0.0f },
	_invulnerabilityWindow{invulnerabilityWindow},
	_isInvulnerable{ false }

{

}
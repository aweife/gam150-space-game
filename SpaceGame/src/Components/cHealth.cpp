/**********************************************************************************
* \file			cHealth.cpp
* \brief		Component for entity that have health/shield and can die
* \author		Jin Kiat, Chong,  80% Code Contribution
*				Wei Feng,   Ang,  20% Code Contribution
*				Long Description
*				- Constructor for component data
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cHealth.h"				//component class declaration

cHealth::cHealth(float shieldMax, float healthMax, float shieldCurr, float healthCurr, float shieldRegenTime, float invulnerabilityWindow) :
	_activateShield{ false },
	_shieldMax{ shieldMax },
	_healthMax{ healthMax },
	_shieldCurr{ shieldCurr },
	_healthCurr{ healthCurr },
	_shieldRegenCooldown{ 0.0f },
	_shieldRegenTime{ shieldRegenTime },
	_invulnerabilityTime{0.0f},
	_invulnerabilityWindow{invulnerabilityWindow},
	_isInvulnerable{ false }

{
	if (shieldMax > 0)	_activateShield = true;
}
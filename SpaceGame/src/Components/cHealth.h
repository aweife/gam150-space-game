/**********************************************************************************
* \file			cHealth.h
* \brief		Component for entity that have health/shield and can die
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Data for health and shield damaged amounts
*				- Data for whether shields is active if not fully damaged
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"


class cHealth:public Component
{
public:
	bool	_activateShield;		// Check for shield activation
	int	_shieldMax;				// Shield max amount
	int	_healthMax;				
	int	_shieldCurr;
	int	_healthCurr;
	float	_shieldRegenCooldown;
	float	_shieldRegenTimer;
	float   _invulnerabilityWindow;
	bool	_isInvulnerable;

	cHealth() = delete;
	cHealth( int shieldMax, int healthMax, float shieldRegenCooldown, float invulnerabilityWindow);
	~cHealth() = default;
};
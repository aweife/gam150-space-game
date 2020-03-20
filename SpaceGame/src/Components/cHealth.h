/**********************************************************************************
* \file			cHealth.h
* \brief		Component for entity that have health/shield and can die
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Data for 
and shield damaged amounts
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
	float	_shieldMax;				// Shield max amount
	float	_healthMax;				
	float	_shieldCurr;
	float	_healthCurr;
	float	_shieldRegenCooldown;	// Timer
	float	_shieldRegenTime;		// The fixed interval
	float   _invulnerabilityTime;	// Timer
	float   _invulnerabilityWindow;	// The fixed interval
	bool	_isInvulnerable;

	cHealth() = delete;
	cHealth( float shieldMax, float healthMax, float shieldCurr, float healthCurr,  float shieldRegenTime, float invulnerabilityWindow);
	~cHealth() = default;
};
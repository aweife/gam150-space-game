#pragma once

class cHealth
{
public:
	float	_shieldMax;				// Shield amount
	bool	_activateShield;		// Check for shield activation
	float	_healthMax;
	float _shieldCurr;
	float _healthCurr;

	cHealth() = default;
	cHealth(float shieldMax, bool activateShield, float healthMax, float shieldCurr, float healthCurr);
	~cHealth() = default;
};
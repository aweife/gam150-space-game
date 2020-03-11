#include "cHealth.h"

cHealth::cHealth(float shieldMax, bool activateShield, float healthMax, float shieldCurr, float healthCurr)
	:_shieldMax{ shieldMax },
	_activateShield{ activateShield },
	_healthMax{ healthMax },
	_shieldCurr{ shieldCurr },
	_healthCurr{ healthCurr }
{

}
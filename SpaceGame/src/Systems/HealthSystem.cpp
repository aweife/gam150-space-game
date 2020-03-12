#include "HealthSystem.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Components/cHealth.h"
#include "../Global.h"


void HealthSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cHealth>());
	Core::Get().SetSystemSignature<HealthSystem>(signature);

}


void HealthSystem::Update()
{

	cHealth* health;

	for (auto const& entity : entitiesList)
	{
		health = Core::Get().GetComponent<cHealth>(entity);

		if(health->_shieldCurr < health->_shieldMax)
		{
			health->_shieldRegenTimer -= g_dt;

			if (health->_shieldRegenTimer <= 0.0f)
			{
				health->_shieldCurr = health->_shieldMax;
				health->_shieldRegenTimer = health->_shieldRegenCooldown;
			}
		}
		
		//if (spaceship->_lives < 0)
		//{
		//	//game over screen, main menu
		//}
		//
		//if(health->_healthCurr <= 0 && spaceship->_lives > 0)
		//{
		//	--spaceship->_lives;
		//	//restart level
		//}
	}
}

void HealthSystem::TakeDamage(ENTITY entity)
{
	cHealth* health;
	health = Core::Get().GetComponent<cHealth>(entity);

	if (!health) return;

	if (health->_shieldCurr > 0)
		--health->_shieldCurr;
	else if (health->_healthCurr > 0)
		--health->_healthCurr;
}
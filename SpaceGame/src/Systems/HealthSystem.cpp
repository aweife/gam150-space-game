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
	signature.set(Core::Get().GetComponentType<cSpaceShip>());
	Core::Get().SetSystemSignature<HealthSystem>(signature);

}


void HealthSystem::Update()
{

	cSpaceShip* spaceship;
	cHealth* health;

	for (auto const& entity : entitiesList)
	{
		health = Core::Get().GetComponent<cHealth>(entity);

		if(health->_shieldCurr <= health->_shieldMax)
		{
			health->_shieldRegenCooldown -= g_dt;

			if (health->_shieldRegenCooldown <= 0)
			{
				++health->_shieldCurr;
				health->_shieldRegenCooldown = health->_shieldRegenTime;
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

	cSpaceShip* spaceship;
	cHealth* health;

	//spaceship = Core::Get().GetComponent<cSpaceShip>(entity);
	health = Core::Get().GetComponent<cHealth>(entity);
	if (!health) return;
	if (health->_shieldCurr > 0 && health->_activateShield)
	{
		--health->_shieldCurr;
		printf("sheild decrease");
	}
	else if (health->_shieldCurr <= 0)
	{
		--health->_healthCurr;
		printf("health decrease");
	}

}
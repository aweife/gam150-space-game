#include "HealthSystem.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Components/cHealth.h"
#include "../Global.h"
#include "../Managers/UIEventsManager.h"					//Broadcasting
#include "../Player/PlayerManager.h"
#include "../ECS/Factory.h"

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
			//Soley to regen
			if (health->_shieldRegenCooldown <= 0)
			{
				health->_shieldCurr +=  10.0f * g_dt;			
				UIEventsManager::Broadcast(new Events::OnShieldChange(health->_shieldCurr));
				
			}
			else
			{
				health->_shieldRegenCooldown -= g_dt;
			}	

			// Change activation
			if (health->_shieldRegenCooldown <= 0 && !health->_activateShield)
			{
				health->_activateShield = true;
			}
		}
		
		if (health->_isInvulnerable)
		{
			health->_invulnerabilityTime -= g_dt;
			if (health->_invulnerabilityTime <= 0)
			{
				health->_isInvulnerable = false;
			}
		}

		if(health->_healthCurr <= 0)
		{
			//restart level
			markedForDestruction.insert(entity);
		}

	}

	if (markedForDestruction.size() > 0)
	{
		for (auto const& entity : markedForDestruction)
		{
			if (entity == PlayerManager::player)
			{
				Factory::RemoveCamera();
				PlayerManager::ResetPlayer();
				PlayerManager::PlayerDeath();
			}
			Core::Get().EntityDestroyed(entity);
		}
		markedForDestruction.clear();
	}
}

void HealthSystem::TakeDamage(ENTITY entity)
{
	cHealth* health;
	health = Core::Get().GetComponent<cHealth>(entity);

	if (health == nullptr) return;

	if (health->_shieldCurr > 0 && health->_activateShield)
	{
		health->_shieldCurr -= 10.0f;
		UIEventsManager::Broadcast(new Events::OnShieldChange(health->_shieldCurr));
		UIEventsManager::Broadcast(new Events::OnShieldActivate());
		health->_shieldRegenCooldown = health->_shieldRegenTime;
		health->_invulnerabilityTime = health->_invulnerabilityWindow;
		health->_isInvulnerable = true;
		if (health->_shieldCurr <= 0)
		{			
			health->_activateShield = false;//cannot use shield for awhile
		}
	}
	else if (health->_healthCurr > 0)
	{
		health->_healthCurr -= 10.0f;
		UIEventsManager::Broadcast(new Events::OnHealthChange(health->_healthCurr));
		health->_invulnerabilityTime = health->_invulnerabilityWindow;
		health->_isInvulnerable = true;
	}

}
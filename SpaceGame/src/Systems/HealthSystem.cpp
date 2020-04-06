/**********************************************************************************
* \file			HealthSystem.cpp
* \brief		Game State for Splash Screen
* \author		Jin Kiat,		Chong,		60% Code Contribution
*				Jun Yi,			Chong,		30% Code Contribution
*				Farzaana Binte, Roslan,     10% Code Contribution
*
*				Long Description
*				- Health and Shield
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "HealthSystem.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Components/cHealth.h"
#include "../Global.h"
#include "../Managers/UIEventsManager.h"					//Broadcasting
#include "../Player/PlayerManager.h"
#include "../ECS/Factory.h"
#include "../Tools/Console.h"
#include "../Managers/LevelManager.h"
#include "../Levels/Level3.h"

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
			//Solely to regen
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

		// If the current shield is 0
		if (entity == PlayerManager::player)
		{

			if (health->_shieldCurr <= 0.1f)
			{
				if (UIEventsManager::Broadcast(new Events::OnShieldDown(true)) == false)
				{
					Factory_UI::CreateShieldsDownInterface();
				}
			}
			else if (health->_shieldCurr >= 10.0f)
			{
				UIEventsManager::Broadcast(new Events::OnShieldDown(false));
			}
			
			if (health->_healthCurr <= 10.0f)
			{
				if (UIEventsManager::Broadcast(new Events::OnLowHealth(true)) == false)
				{
					Factory_UI::CreateLowHealthInterface();
				}

			}
			else if (health->_healthCurr > 10.0f)
			{
				UIEventsManager::Broadcast(new Events::OnLowHealth(false));
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
				PlayerManager::PlayerDeath();
			}
			//Check for enemy WAVES
			cRigidBody* collision = Core::Get().GetComponent<cRigidBody>(entity);
			if (collision)
			{
				if (collision->_tag == COLLISIONTAG::WAVEENEMY || collision->_tag == COLLISIONTAG::ENEMY)
				{
					LevelManager::ClearEnemy(entity);
				}
				else if (collision->_tag == COLLISIONTAG::ESCORT)
				{
					//escort has died
					Factory::RemoveCamera();
					EscortDeath();
				}
				else if (collision->_tag == COLLISIONTAG::BOSS)
				{
					// Boss has died
					LevelManager::DefeatBoss();
				}
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
		if (health->_shieldCurr < 0.0f)	health->_shieldCurr = 0.0f;
		if (entity == PlayerManager::player)
		{
			UIEventsManager::Broadcast(new Events::OnShieldChange(health->_shieldCurr));
			UIEventsManager::Broadcast(new Events::OnShieldActivate());
		}
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
		//Floating damage UI
		if (entity != PlayerManager::player)
		{
			Factory_UI::CreateUI_FloatingDamage(entity, static_cast<int>(health->_healthCurr), static_cast<int>(10.0f));
		}

		health->_healthCurr -= 10.0f;
		if (health->_healthCurr < 0.0f) health->_healthCurr = 0.0f;
		if (entity == PlayerManager::player)
		UIEventsManager::Broadcast(new Events::OnHealthChange(health->_healthCurr));
		health->_invulnerabilityTime = health->_invulnerabilityWindow;
		health->_isInvulnerable = true;
	}

}
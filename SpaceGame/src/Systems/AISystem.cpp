/*********************************************************************************
* \file			AISystem.cpp
* \brief		Controls the behaviour for AI (FSM)
* \author		Ang Wei Feng, 100% Code Contribution
*
*				This system loops through all ai components in the game and calls
*				their Run function, updating the state of every ai agent.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AISystem.h"							//Self Header
#include "../ECS/Core.h"						//Work with ECS
#include "../Components/ComponentList.h"		//Get necessary component references
#include "../Global.h"
#include <variant>
#include "../ECS/Factory.h"
#include "UISystem.h"							//Spawn Ai Indicators
#include "../Player/PlayerManager.h"			// Update ai on player
#include "../Levels/Level3.h"					// For level 3 escort mission
#include "../Managers/GameStateManager.h"
/******************************************************************************/
/*!
  \brief	Sets the system signature for this system based on components required
*/
/******************************************************************************/
void AISystem::Init()
{
	SIGNATURE signature;

	//Set the bits for necessary components
	signature.set(Core::Get().GetComponentType<cAI>());

	//Assign the signature for this System
	Core::Get().SetSystemSignature<AISystem>(signature);
}

void AISystem::Update()
{
	cAI* ai;

	ENTITY pid;
	if (currentState == GS_LEVEL3)
	{
		// If level 3, main target is escort
		pid = GetEscort();

		// When escort dies
		if (pid == 0)
		{
			// If mission pass, main target becomes player
			if (EscortMissionSuccess())
				pid = PlayerManager::player;
			else // Else game ends
				pid = 0;
		}
	}
	else
	{
		pid = PlayerManager::player;
	}

	//NO ACTIVE PLAYER
	if (pid == 0)	return;

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		ai = Core::Get().GetComponent<cAI>(entity);

		// Update this ai's blackboard
		ai->_blackboard.UpdateBlackboard();

		// Run this ai's current state
		std::visit([&](auto& state)
			{
				state.Run(ai->_blackboard, ai->_currentState);
			}, ai->_currentState.states);

		CheckOutOfScreen(entity);

		// Check if ai is destroyed in the states, add to our destroy set
		if (ai->_blackboard.markedForDestruction)
			markedForDestruction.insert(entity);
	}

	if (markedForDestruction.size() > 0)
	{
		for (auto const& entity : markedForDestruction)
		{
			Core::Get().EntityDestroyed(entity);
		}
		markedForDestruction.clear();
	}
}

void AISystem::OnComponentAdd(ENTITY) {};
void AISystem::OnComponentRemove(ENTITY) {};

void AISystem::CheckOutOfScreen(ENTITY id)
{
	cTransform* self = Core::Get().GetComponent<cTransform>(id);

	// If ai is destroyed, dont update
	if (!self) return;

	AEVec2 cameraPosition = { 0 };
	AEGfxGetCamPosition(&cameraPosition.x, &cameraPosition.y);

	if (!(self->_position.x > cameraPosition.x - g_WorldMaxX && self->_position.x < cameraPosition.x + g_WorldMaxX
		&& self->_position.y > cameraPosition.y - g_WorldMaxY && self->_position.y < cameraPosition.y + g_WorldMaxY))
	{
		AEVec2 relativeDirection;
		AEVec2Sub(&relativeDirection, &self->_position, &cameraPosition);

		//Out of screen, but not extremely far away
		float maximumDistance = sqrt(g_WorldMaxX * g_WorldMaxX + g_WorldMaxY * g_WorldMaxY) * 1.05f;
		if (AEVec2Length(&relativeDirection) <= maximumDistance)
		{
			std::shared_ptr<UISystem> uiSys(std::static_pointer_cast<UISystem>(Core::Get().GetSystem<UISystem>()));
			//@TED later just change the last variable for different enemy type
			uiSys->Check_IndicatorExist(id, relativeDirection, 0); //Under UI System
		}
	}
}
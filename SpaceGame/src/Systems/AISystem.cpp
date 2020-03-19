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

	const ENTITY pid = PlayerManager::player;
	if (pid == 0)	return;				//NO ACTIVE PLAYER

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		ai = Core::Get().GetComponent<cAI>(entity);

		// Update this ai's blackboard
		UpdateBlackboard(ai->_blackboard, entity);

		// Run this ai's current state
		std::visit([&]( auto& state ) 
		{
			state.Run( ai->_blackboard, ai->_currentState );
		}, ai->_currentState.states );

		CheckOutOfScreen(entity);

	}
}

void AISystem::OnComponentAdd(ENTITY) {};
void AISystem::OnComponentRemove(ENTITY) {};

void AISystem::UpdateBlackboard(aiBlackBoard& bb, ENTITY id)
{
	// Set ids
	bb.id = id;
	const ENTITY pid = PlayerManager::player;
	if (pid == 0)	return;				//NO ACTIVE PLAYER

	// Get components
	cTransform* self = Core::Get().GetComponent<cTransform>(id);
	cTransform* player = Core::Get().GetComponent<cTransform>(pid);
	
	// Calculate distance
	bb.distanceFromPlayer = AEVec2Distance(&player->_position, &self->_position);

	// Calculate vector towards player
	AEVec2 temp;
	AEVec2Sub(&temp, &player->_position, &self->_position);
	bb.directionToPlayer = temp;
	AEVec2Normalize(&temp, &temp);
	bb.directionToPlayerN = temp;

	// Update player last known position
	bb.positionUpdateTimer += g_dt;
	if (bb.positionUpdateTimer > 2.0f)
	{
		bb.positionUpdateTimer = 0.0f;

		// Store
		bb.playerLastKnownPos = player->_position;
	}
}

void AISystem::CheckOutOfScreen(ENTITY id)
{
	cTransform* self = Core::Get().GetComponent<cTransform>(id);

	AEVec2 cameraPosition = { 0 };
	AEGfxGetCamPosition(&cameraPosition.x, &cameraPosition.y);

	if (!(self->_position.x > cameraPosition.x - g_WorldMaxX && self->_position.x < cameraPosition.x + g_WorldMaxX
		&& self->_position.y > cameraPosition.y - g_WorldMaxY && self->_position.y < cameraPosition.y + g_WorldMaxY))
	{
		AEVec2 relativeDirection;
		AEVec2Sub(&relativeDirection, &self->_position, &cameraPosition);
		std::shared_ptr<UISystem> uiSys(std::static_pointer_cast<UISystem>(Core::Get().GetSystem<UISystem>()));	
		
		//@TED later just change the last variable for different enemy type
		uiSys->Check_AIIndicatorExist(id, relativeDirection, 0); //Under UI System
	}
}
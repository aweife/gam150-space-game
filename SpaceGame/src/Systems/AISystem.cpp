/*********************************************************************************
* \file			AISystem.cpp
* \author		Ang Wei Feng
* \version		2.0
* \date			28/02/2020
* \par			AI Pillar/System Code
* \note			Course: GAM150
* \brief		Controls the behaviour for AI

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AISystem.h"							//Self Header
#include "../ECS/Core.h"						//Work with ECS
#include "../Components/ComponentList.h"		//Get necessary component references
#include "../Global.h"
#include <variant>

/******************************************************************************/
/*!
  \brief	Sets the system signature for this system based on components required
*/
/******************************************************************************/
void AISystem::Init()
{
	SIGNATURE signature;
	//Set the bits for necessary components
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cPathFinding>());
	signature.set(Core::Get().GetComponentType<cAI>());
	//Assign the signature for this System
	Core::Get().SetSystemSignature<AISystem>(signature);
}

float timer = 0.0f;
bool shouldUpdate = false;

void AISystem::Update()
{
	cTransform* trans;
	cRigidBody* rb;
	cPathFinding* path;
	cAI* ai;

	cTransform* targetTrans;
	cRigidBody* targetRb;

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		trans = Core::Get().GetComponent<cTransform>(entity);
		rb = Core::Get().GetComponent<cRigidBody>(entity);
		ai = Core::Get().GetComponent<cAI>(entity);
		path = Core::Get().GetComponent<cPathFinding>(entity);

		// Get target
		targetTrans = Core::Get().GetComponent<cTransform>(path->target);
		targetRb = Core::Get().GetComponent<cRigidBody>(path->target);

		// Update ai's blackboard
		ai->_blackboard.distanceFromPlayer = AEVec2Distance(&trans->_position, &targetTrans->_position);

		std::visit([&]( auto& state ) 
		{
			state.Run( ai->_blackboard, ai->_currentState );
		}, ai->_currentState.m_Varient );
	}
}

void AISystem::OnComponentAdd(ENTITY) {};
void AISystem::OnComponentRemove(ENTITY) {};
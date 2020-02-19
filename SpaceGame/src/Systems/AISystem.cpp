/*********************************************************************************
* \file			AISystem.cpp
* \author		Ang Wei Feng
* \version		1.0
* \date			13/02/2019
* \par			AI Pillar/System Code
* \note			Course: GAM150
* \brief		Controls the behaviour for AI

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AISystem.h"							//Self Header
#include "../ECS/Core.h"						//Work with ECS
#include "../Components/ComponentList.h"		//Get necessary component references
#include "../Global.h"

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
	timer += g_dt;
	if (timer > 0.75f)
	{
		timer = 0.0f;
		shouldUpdate = true;
	}

	if (!shouldUpdate)
		return;

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

		float distanceToPlayer = AEVec2Distance(&trans->_position, &targetTrans->_position);

		// If too close to player
		if (distanceToPlayer < ai->minDistance)
		{
			path->currentState = PATH_FLEE;
			if (rb->_velocity < targetRb->_velocity)
				rb->_velocity += 30.0f;
		}
		else if (distanceToPlayer > ai->maxDistance)
		{
			path->currentState = PATH_SEEK;
			if (rb->_velocity < targetRb->_velocity)
				rb->_velocity += 30.0f;
		}
		else
		{
			if (rb->_velocity > targetRb->_velocity/2.0f)
				rb->_velocity -= 15.0f;
			printf("ATTACKING PLAYER\n");

		}

		/*if can - move - away - from - player
			AND(damage - taken > morale
				OR too - close - to - player)
			move - away - from - player
		else if can - move - toward - player
			AND damage - taken < morale
			AND too - far - from - player
			move - toward - player
		else if can - attack - player
			attack - player
		else stand - still*/

		shouldUpdate = false;
	}
}

void AISystem::OnComponentAdd(ENTITY) {};
void AISystem::OnComponentRemove(ENTITY) {};
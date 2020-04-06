/*********************************************************************************
* \file			SpaceShipLogicSystem.h
* \brief		Logic Systems for all Spaceships
* \author		Chong Jin Kiat, 90% Code Contribution
* \author		Ang Wei Feng, 10% Code Contribution
*
*				Logic System for Spaceship that has thrusting capabilities.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"
#include "../Tools/Editor.h"

#include "../ECS/Factory.h"

#include "../Managers/CameraManager.h"					//Testing....remove once screenshake is done
#include "../Managers/UIEventsManager.h"
#include "../Player/PlayerManager.h"
/******************************************************************************/
/*!
	Global Variables
*/
/******************************************************************************/

void SpaceShipLogicSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cSpaceShip>());
	Core::Get().SetSystemSignature<SpaceShipLogicSystem>(signature);
}

void SpaceShipLogicSystem::Update()
{
	cTransform* transform;
	cRigidBody* rigidbody;
	cSpaceShip* spaceship;
	cHealth*    health;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity);
		spaceship = Core::Get().GetComponent<cSpaceShip>(entity);
		health    = Core::Get().GetComponent<cHealth>(entity);

		//Time update
		//Cooldown slower when overheat;
		if (spaceship->_overheatThrusterCurr > 0.0f && spaceship->_thrustDelayCurr > 0.0f)
		{
			spaceship->_thrustDelayCurr -= g_dt * 0.7f;
			if (spaceship->_thrustDelayCurr < 0.0f)
			{
				spaceship->_overheatThrusterCurr = 0.0f;
			}
		}
		//Normal cooldown rate
		else
		{
			spaceship->_thrustDelayCurr -= g_dt;
		}

		// If spaceship is not overheating
		if (spaceship->_isThrusting && spaceship->_thrustDelayCurr <= 0.0f)
		{
			SpaceShipThrust(rigidbody, transform);
			Factory::CreateParticleEmitter_TRAIL(transform);
			
			// Increase terminal velocity
			rigidbody->_velocityCap = rigidbody->_velocityHardCap;

			if (rigidbody->_velocity >= rigidbody->_velocityHardCap)
			{
				spaceship->_overheatThrusterCurr += g_dt;
			}

			if (spaceship->_overheatThrusterCurr > spaceship->_overheatThruster)
			{
				spaceship->_thrustDelayCurr = spaceship->_thrustDelay;
			}
		}
		else
		{
			// Main terminal velocity
			rigidbody->_velocityCap = rigidbody->_velocitySoftCap;

			//Cooldown thrusters
			if (spaceship->_overheatThrusterCurr > 0.0f)
			{
				spaceship->_overheatThrusterCurr -= g_dt;
			}
		}

		if (entity == PlayerManager::player)
		{
			UIEventsManager::Broadcast(new Events::OnThrusterChange(rigidbody->_velocity, rigidbody->_velocityHardCap
				, spaceship->_overheatThrusterCurr, spaceship->_overheatThruster));
			Editor_TrackVariable("Player Velocity ", rigidbody->_velocity);
		}


	}
}

void SpaceShipThrust(cRigidBody* rb, cTransform* transform)
{
	// New Thrust direction to apply ontop of ship current velocity
	AEVec2Set(&rb->_velocityDirection, AECos(transform->_rotation), AESin(transform->_rotation));
	AEVec2Set(&rb->_steeringVector, AECos(transform->_rotation), AESin(transform->_rotation));

	// Accelerate
	rb->_velocity += rb->_acceleration;
}

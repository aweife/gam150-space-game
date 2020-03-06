#include "SpaceShipLogicSystem.h"
#include "WeaponSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"

#include "../ECS/Factory.h"
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
	signature.set(Core::Get().GetComponentType<cRangeWeapon>());
	Core::Get().SetSystemSignature<SpaceShipLogicSystem>(signature);
}


void SpaceShipLogicSystem::Update()
{
	cTransform* transform;
	cRigidBody* rigidbody;
	cSpaceShip* spaceship;
	cRangeWeapon* rangeweapon;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity); 
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity); 
		spaceship = Core::Get().GetComponent<cSpaceShip>(entity);
		rangeweapon = Core::Get().GetComponent<cRangeWeapon>(entity);

		//Time update
		rangeweapon->_fireRate += g_dt;
		spaceship->_thrustDelay += g_dt;

		if (spaceship->_isThrusting /*&& spaceship->_thrustDelay > 1.5f*/)
		{
			//spaceship->_thrustDelay = 0.0f;
			SpaceShipThrust(rigidbody, transform);
		}

	}
}

//OUTSIDE OF NAMESPACE for helper functions

void SpaceShipThrust(cRigidBody* rb, cTransform* transform, cSpaceShip* spaceship)
{
	AEVec2 thrustDir, thrustVector;

	// New Thrust direction to apply ontop of ship current velocity
	AEVec2Set(&thrustDir, AECos(transform->_rotation), AESin(transform->_rotation));

	// Thrust vector will be added onto velocity, based on rate of change (acceleration)
	AEVec2Scale(&thrustVector, &thrustDir, rb->_acceleration + spaceship->_thrustSpeedAddition);

	// Add Thrust Vector to current velocity
	AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &thrustVector);

	if (AEVec2Length(&rb->_velocityVector) >= rb->_velocityCap)
	{
		AEVec2Scale(&rb->_velocityVector, &rb->_velocityVector, 0.99f);		//Smootly reduce velocity
	}
}


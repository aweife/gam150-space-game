#include "SpaceShipLogicSystem.h"
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
	Core::Get().SetSystemSignature<SpaceShipLogicSystem>(signature);
}


void SpaceShipLogicSystem::Update()
{
	cTransform* transform;
	cRigidBody* rigidbody;
	cSpaceShip* spaceship;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity); 
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity); 
		spaceship = Core::Get().GetComponent<cSpaceShip>(entity); 

		//Time update
		spaceship->_shootDelay += g_dt;
		spaceship->_thrustDelay += g_dt;

		if (spaceship->_isThrusting /*&& spaceship->_thrustDelay > 1.5f*/)
		{
			//spaceship->_thrustDelay = 0.0f;
			SpaceShipThrust(rigidbody, transform);
		}

		if (spaceship->_isShooting && spaceship->_shootDelay > 1.5f)
		{
			spaceship->_shootDelay = 0.0f;
			SpaceShipShoot(transform);
		}
	}
}

//OUTSIDE OF NAMESPACE for helper functions

void SpaceShipThrust(cRigidBody* rb, cTransform* transform)
{
	AEVec2 thrustDir, thrustVector;

	// New Thrust direction to apply ontop of ship current velocity
	AEVec2Set(&thrustDir, AECos(transform->_rotation), AESin(transform->_rotation));

	// Thrust vector will be added onto velocity, based on rate of change (acceleration)
	AEVec2Scale(&thrustVector, &thrustDir, rb->_acceleration);

	// Add Thrust Vector to current velocity
	AEVec2Add(&rb->_velocityVector, &rb->_velocityVector, &thrustVector);

	if (AEVec2Length(&rb->_velocityVector) >= rb->_velocityCap)
	{
		AEVec2Scale(&rb->_velocityVector, &rb->_velocityVector, 0.99f);		//Smootly reduce velocity
	}
}


// This should move to weapons system
void SpaceShipShoot(cTransform* transform)
{
		AEVec2 bulletDirection;
		AEVec2 bulletVelocity;

		// Setting the direction of bullet spawn
		AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
		// Bullet velocity
		AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
		// Spawn the bullet at the tip of player
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * 100.0f,
			transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, transform->_rotation + PI / 2);
}
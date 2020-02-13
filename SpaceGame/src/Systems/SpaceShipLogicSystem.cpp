#include "SpaceShipLogicSystem.h"
#include <AEVec2.h>
#include "../Global.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"


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
		transform = Core::Get().GetComponent<cTransform>(entity); // Does not link properly
		rigidbody = Core::Get().GetComponent<cRigidBody>(entity); // Does not link properly
		spaceship = Core::Get().GetComponent<cSpaceShip>(entity); // Does not link properly


		if (spaceship->_isThrusting && spaceship->_thrustDelay > 1.5f)
		{
			spaceship->_thrustDelay = 0.0f;
			transform->_position.x += rigidbody->velocityVector.x;
			transform->_position.y += rigidbody->velocityVector.y;

		}

		if (spaceship->_isShooting && spaceship->_shootDelay > 1.5f)
		{
			spaceship->_shootDelay = 0.0f;
			transform->_position.x += rigidbody->velocityVector.x;
			transform->_position.y += rigidbody->velocityVector.y;
		}
	}
}

void SpaceShipLogicSystem::Render() {}
void SpaceShipLogicSystem::OnComponentAdd(ENTITY) {};
void SpaceShipLogicSystem::OnComponentRemove(ENTITY) {};

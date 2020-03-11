#pragma once

#include "System.h"					//Inheritance
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"
#include "../Components/cSpaceShip.h"

class SpaceShipLogicSystem : public System
{
public:
	SpaceShipLogicSystem() = default;					//Virtual Constructor...
	~SpaceShipLogicSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

void SpaceShipThrust(cRigidBody* rb, cTransform* transform, cSpaceShip* spaceship);
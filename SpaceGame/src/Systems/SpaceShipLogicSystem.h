/*********************************************************************************
* \file			SpaceShipLogicSystem.h
* \brief		Logic Systems for all Spaceships
* \author		Chong Jin Kiat, 100% Code Contribution
*
*				Logic System for Spaceship that has thrusting capabilities.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

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

void SpaceShipThrust(cRigidBody* rb, cTransform* transform);
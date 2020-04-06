/**********************************************************************************
* \file			SpaceShipLogicSystem.h
* \brief		Logic for spaceship
* \author		Jin Kiat,		Chong,		90% Code Contribution
*				Jun Yi,			Chong,		10% Code Contribution
*
*				Long Description
*				- thrust logic
*				- particles for player
*				- ship movement
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
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
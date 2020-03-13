/*********************************************************************************
* \file			WeaponSystemRange.h
* \brief		Controls the range weapon of every entities
* \author		Chong Jin Kiat, 75% Code Contribution
* \author		Ang Wei Feng, 25% Code Contribution
*
*				This system loops through all its components in the game and make
*				sure they fire at their respective speed and delays
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "System.h"									// Inheritance
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"
#include "../Components/cWeapon.h"

class WeaponSystemRange : public System
{
public:
	WeaponSystemRange() = default;					// Virtual Constructor...
	~WeaponSystemRange() = default;					// ...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};


void NormalShoot(cTransform* transform, OWNERTAG tag);
void HomingShoot(cTransform* transform);
void MachineGunShoot(cTransform* transform);

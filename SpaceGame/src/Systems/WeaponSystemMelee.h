/*********************************************************************************
* \file			WeaponSystemMelee.h
* \brief		Controls the melee weapon of every entities
* \author		Chong Jin Kiat, 100% Code Contribution
*
*				Melee System for player combat
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once

#include "System.h"					//Inheritance

class WeaponSystemMelee : public System
{
public:
	WeaponSystemMelee() = default;					//Virtual Constructor...
	~WeaponSystemMelee() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

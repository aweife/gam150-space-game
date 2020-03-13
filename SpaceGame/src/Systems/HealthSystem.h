/**********************************************************************************
* \file			HealthSystem.h
* \brief		Game State for Splash Screen
* \author		Jin Kiat,		Chong,		70% Code Contribution
*				Jun Yi,			Chong,		30% Code Contribution
*				
*				Long Description
*				- Health and Shield
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "System.h"
#include <set>
class HealthSystem : public System
{
public:
	std::set<ENTITY> markedForDestruction;

	HealthSystem() = default;					//Virtual Constructor...
	~HealthSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};

	void TakeDamage(ENTITY entity);
};
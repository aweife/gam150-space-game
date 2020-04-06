/*********************************************************************************
* \file			ProjectileSystem.h
* \brief		Logic Different types of Projectiles 
* \author		Chong Jin kiat, 100% Code Contribution
*
*				Logic Different types of Projectiles 
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once
#include "System.h"
#include <set>
#include "AEVec2.h"

class ProjectileSystem : public System
{
public:
	std::set<ENTITY> objToDestory;
	ProjectileSystem() = default;					//Virtual Constructor...
	~ProjectileSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
	void HomingTarget(AEVec2& targetPos, AEVec2& selfPos, AEVec2& velCurr, AEVec2& steering, float& dirCurr);
};
/*********************************************************************************
* \file			PhysicsSystem.h
* \brief		Physics system to control various physics interaction by entity
* \author		Farzaana Binte Roslan, 100% Code Contribution
*
*				Physics system to control various physics interaction by entity
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "System.h"				//Inheritance
#include "AEVec2.h"             //AEVec2


bool foranglecheck(AEVec2 currdir, AEVec2 newdir);

class PhysicsSystem : public System
{
public: 
	PhysicsSystem() = default;
	~PhysicsSystem() = default;

	void Init() override;
	void Render() override {};
	void Update() override;
	void OnComponentAdd(ENTITY entity) override;
	void OnComponentRemove(ENTITY entity) override;
};


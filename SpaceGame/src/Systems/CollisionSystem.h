/*********************************************************************************
* \file			CollisionSystem.h
* \brief		Collision system to manage the component component
* \author		Farzaana Binte Roslan, 100% Code Contribution
*
*				Collision system to manage the component component
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once

#include "System.h"								//Inheritance

class CollisionSystem : public System
{
private:
	std::set<ENTITY> markedForDestruction;					//Cant delete entity while looping with range loop
public:
	CollisionSystem() = default;
	~CollisionSystem() = default;
	void Init() override;
	void Render() override;
	void Update() override;
	void OnComponentAdd(ENTITY entity) override;
	void OnComponentRemove(ENTITY entity) override;
};
/*********************************************************************************
* \file			TimelineSystem.h
* \brief		Creating UI for different parts of the game
* \author		Chong Jun Yi, 100% Code Contribution
*
*				Timeline system for manipulating values function over a period of time.
*				and has looping capabilities.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "System.h"					//Inheritance

class TimelineSystem : public System
{
public:
	TimelineSystem() = default;					//Virtual Constructor...
	~TimelineSystem() = default;					//...and destructor

	std::set<ENTITY> markedForRemoval;

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

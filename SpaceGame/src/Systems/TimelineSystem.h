/**********************************************************************************
* \file			TimelineSystem.h
* \brief		Update timelines
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Int, floats, bools, functions
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
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

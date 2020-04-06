/**********************************************************************************
* \file			WarpingSystem.h
* \brief		Handles wrapping on screen
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Handles wrapping around screen coords
*				- mostly for menu
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "System.h"					//Inheritance

class WarpingSystem : public System
{
public:
	WarpingSystem() = default;					//Virtual Constructor...
	~WarpingSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

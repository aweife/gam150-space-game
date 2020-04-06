/*********************************************************************************
* \file			WarpingSystem.h
* \brief		Wrapping UI and game entity in the game.
* \author		Chong Jun Yi, 100% Code Contribution
*
*				Wrapping User Interface, Game Entities in the game
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
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

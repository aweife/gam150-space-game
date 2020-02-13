#pragma once
/*********************************************************************************
* \file			PhysicsSystem.h
* \author		Farzaana Binte Roslan
* \version		1.0
* \date			31/01/2020
* \par			Systems
* \note			Course: GAM150
* \brief		Physics system to control various physics manager
				-

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "System.h"

class PhysicsSystem : public System
{
public: 
	void Init() override;
	void Update() override;
	void Render() override;
};


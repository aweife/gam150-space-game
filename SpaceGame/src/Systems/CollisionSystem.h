#pragma once


#include "../Global.h"
#include "../Components/Component.h"
#include "System.h"
/*********************************************************************************
* \file			CollisionSystem.h
* \author		Farzaana Binte Roslan
* \version		1.0
* \date			31/01/2020
* \par			Systems
* \note			Course: GAM150
* \brief		Collision system to manage the component component

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#include "../Components/cCollision.h"


class CollisionSystem : public System
{
public:
	void Init();

	void Update();
};
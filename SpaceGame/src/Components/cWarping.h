/**********************************************************************************
* \file			cWarping.h
* \brief		Warping
* \author		Jun Yi,		Chong,  100% Code Contribution
*
*				Handles the warping component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "AEEngine.h"
#include "Component.h"

class cWarping :public Component
{
public:
	AEVec2 _warpX = { 0 };
	AEVec2 _warpY = { 0 };

	cWarping() = delete;
	cWarping(AEVec2 warpX, AEVec2 warpY);
};
/*********************************************************************************
* \file			Input.cpp
* \author		Chong Jin Kiat
* \version		2.0
* \date			17/02/2020
* \par			Input
* \note			Course: GAM150
* \brief		Handles global input. All related player logic will pass to PlayerManager
				- player input during gameplay
				- player input during upgrades (no game simulation)
				- player input during menus

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

namespace InputManager
{
	// -----------------------------------------------------------------------
	// Mouse Variables
	// -----------------------------------------------------------------------
	extern int			mousePosX;				// Computer mouse screen position in X coordinates
	extern int			mousePosY;				// Computer mouse screen position in Y coordinates
	extern bool			mouseRTrigger;
	extern bool			mouseLTrigger;

	void Update();
}
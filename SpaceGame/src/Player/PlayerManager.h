/**********************************************************************************
* \file			PlayerManager.h
* \brief		Logic for player features from input
* \author		Jin Kiat,		Chong,		90% Code Contribution
*				Jun Yi,			Chong,		10% Code Contribution
*
*				Long Description
*				- facing direction
*				- mouse clicks on UI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "../Global_ECS.h"				// Entity reference
#include "../Components/cRigidBody.h"	// Slowly rotate to face mouse
#include "../Components/cTransform.h"	// Get player position
#include "../Components/cWeapon.h"
#include "../Components/cSpaceShip.h"
#include "../Components/cHealth.h"

namespace PlayerManager
{
	extern ENTITY player;					//Current player must be non-zero to have any control
	extern bool playerProgressInit;
	extern cRangeWeapon playerRangeProgression;
	extern cMeleeWeapon playerMeleeProgression;
	extern cSpaceShip playerSpaceshipProgression;
	extern cHealth playerHealthProgression;

	void Update();
	
	void RotateWithMouse(int mousePosX, int mousePosY, cTransform* camTransform,
		cTransform* playerTransform, cRigidBody* playerRigidBody);

	void CreatePlayerWeapon();
	void ResetPlayer();	
	void PlayerDeath();
}
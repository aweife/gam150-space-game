/**********************************************************************************
* \file			PlayerManager.cpp
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
#include "PlayerManager.h"						// Self Header
#include "../Global.h"							// Screensize 
#include "../Managers/InputManager.h"			// Recieve inputs
#include "../Managers/ManagerList.h"	        // For UI manager
#include "../ECS/Core.h"						// Get Component
#include "../Managers/CameraManager.h"			// Get the position of a moving camera 
#include "../Math/Math.h"						// Rotation Lerp
//#include "../Components/cSpaceShip.h"			// Mouse click ->shooting
//#include "../Components/cWeapon.h"				// Mouse click ->shooting

#include "../Tools/Editor.h"					// Debugging
#include "../ECS/Factory.h"						// Gameover UI

namespace PlayerManager
{
	ENTITY		player			= 0;
	float		angle			= 0.0f;			// Angle between mouse position and player

	bool playerProgressInit = false;
	cRangeWeapon playerRangeProgression;
	cMeleeWeapon playerMeleeProgression;
	cSpaceShip playerSpaceshipProgression;
	cHealth playerHealthProgression;

	void Update()
	{
		if (!player) return;					// No active player to control if ENTITY = zero

		cRigidBody* playerRigidBody = Core::Get().GetComponent<cRigidBody>(player);
		cTransform* playerTransform = Core::Get().GetComponent<cTransform>(player); 
		cSpaceShip* playerSpaceShip = Core::Get().GetComponent<cSpaceShip>(player);
		cRangeWeapon* playerWeapon = Core::Get().GetComponent<cRangeWeapon>(player);
		cTransform* camTransform = CameraManager::GetCameraTransform();
		int mousePosX = InputManager::mousePosX;
		int mousePosY = InputManager::mousePosY;
			
		RotateWithMouse(mousePosX, mousePosY, camTransform, playerTransform, playerRigidBody);

		playerSpaceShip->_isThrusting = InputManager::mouseRTrigger;
		if (playerSpaceShip->_currWeaponMode == WeaponMode::WEAPONMODE_RANGE)
		{
			playerWeapon->_playerIsShooting = InputManager::mouseLTrigger;
		}
	}

	void RotateWithMouse(int mousePosX, int mousePosY, cTransform* camTransform, 
		cTransform* playerTransform, cRigidBody* playerRigidBody)
	{
		// -----------------------------------------------------------------------
		// Convert mouse screen space to global space (with moving camera)
		// -----------------------------------------------------------------------
		//Move the point of origin from top left to center
		float worldMousePosX = static_cast<float>(mousePosX) - g_WindowWidth / 2.0f;
		// Calculate mouse X position in world space
		if(camTransform != nullptr)		worldMousePosX += camTransform->_position.x;

		//Move the point of origin from top left to center
		float worldMousePosY = -1 * (static_cast<float>(mousePosY) - g_WindowHeight / 2.0f);
		// Calculate mouse Y position in world space
		if (camTransform != nullptr)	worldMousePosY += camTransform->_position.y;

		// -----------------------------------------------------------------------
		// Global Space: calculate relative vector direction to player
		// -----------------------------------------------------------------------
		float dirX = worldMousePosX - playerTransform->_position.x;
		float dirY = worldMousePosY - playerTransform->_position.y;
		float length = sqrtf(dirX * dirX + dirY * dirY);

		/*Editor_TrackVariable("A", camTransform->_position.x);
		Editor_TrackVariable("B", playerTransform->_position.x);
		Editor_TrackVariable("C", dirX);*/

		//Make sure mouse is a certain distance away before calculating
		if (length > playerTransform->_scale.x / 2)
		{
			// Angle between mouse and player based on vector
			angle = atan2(dirY, dirX);
			Editor_TrackVariable("Angle", AERadToDeg(angle));

			// Set player to point at mouse position
			playerTransform->_rotation = MBMath_LerpRotation(playerTransform->_rotation, angle,
				g_dt * playerRigidBody->_rotateVelocity);
		}
	}

	void CreatePlayerWeapon()
	{
		playerRangeProgression	= cRangeWeapon{ OWNERTAG::PLAYER, WeaponType::pistol, 1.0f, 0.25f };
		playerMeleeProgression	= cMeleeWeapon{};
		playerSpaceshipProgression = cSpaceShip{ false, 2.0f, WeaponMode::WEAPONMODE_RANGE };
		playerHealthProgression = cHealth{ 30.0f, 30.0f, 30.0f, 30.0f, 4.0f, 1.0f };
		playerProgressInit = true;
	}

	void ResetPlayer(bool hardReset)
	{
		player = 0;
		if (hardReset)
		{
			playerProgressInit = false;
		}
	}
	
	void PlayerDeath()
	{
		ResetPlayer();

		Factory_UI::CreateUI_GameOver();
		LevelManager::ClearObjectiveAll();
	}
}
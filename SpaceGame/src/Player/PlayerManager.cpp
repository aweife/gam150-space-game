#include "PlayerManager.h"						//Self Header
#include "../Global.h"
#include "../Managers/InputManager.h"			//Recieve inputs
#include "../ECS/Core.h"
#include "../Managers/CameraManager.h"
#include "../Math/Math.h"						// Rotation Lerp
#include "../Components/cSpaceShip.h"
#include "../Components/cWeapon.h"

#include "../Tools/Editor.h"					//Debugging
#include "../ECS/Factory.h"
namespace PlayerManager
{
	ENTITY		player			= 0;
	float		angle			= 0.0f;			// Angle between mouse position and player
	
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
		if (playerSpaceShip->_currWeaponMode == WeaponMode::range)
			playerWeapon->_isShooting = InputManager::mouseLTrigger;
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
		worldMousePosX += camTransform->_position.x;

		//Move the point of origin from top left to center
		float worldMousePosY = -1 * (static_cast<float>(mousePosY) - g_WindowHeight / 2.0f);
		// Calculate mouse Y position in world space
		worldMousePosY += camTransform->_position.y;

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

	void ResetPlayer()
	{
		player = 0;
	}
	void PlayerDeath()
	{
		Factory_UI::CreateUI_GameOver();
	}
}
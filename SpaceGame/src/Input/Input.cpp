/*********************************************************************************
* \file			Input.cpp
* \author		Chong Jin Kiat
* \version		1.0
* \date			31/01/2020
* \par			Input
* \note			Course: GAM150
* \brief		Gets player input.
				-

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#include "Input.h"
#include "AEEngine.h" 
#include "../Components/cRigidBody.h"
#include "../Components/cTransform.h"
#include "../ECS/Core.h"
#include "../Global.h"				//delta time
#include "../Managers/CameraManager.h"

/******************************************************************************/
/*!
	Player Variables
*/
/******************************************************************************/
float		playerPosX			= 0.0f; // Player current position in the X coordinates
float		playerPosY			= 0.0f; // Player current position in the Y coordinates
float		playerVelX			= 0.0f; // Player current velocity in the X coordinates
float		playerVelY			= 0.0f; // Player current velocity in the Y coordinates
float		airResistance		= 0.0f; // Air Resistance 
float		playerRotation		= 0.0f; // Player current rotation speed
float		trusterSpeed		= 0.0f; // Thruster speed
float		bulletSpeed			= 0.0f; // Bullet speed
const float	playerSpeed = 1.0f;

/******************************************************************************/
/*!
	World/Other Variables
*/
/******************************************************************************/
float		worldMinX			= 0.0f; // World(Game) screen minimum X coordinates
float		worldMaxX			= 0.0f; // World(Game) screen maximum X coordinates
float		worldMinY			= 0.0f; // World(Game) screen minimum Y coordinates
float		worldMaxY			= 0.0f; // World(Game) screen maximum Y coordinates

int			mousePosX			= 0; // Computer screen mouse position in X coordinates
int			mousePosY			= 0; // Computer screen mouse position in Y coordinates

int*		pMousePosX			= &mousePosX; // Pointer to computer screen mouse position in X coordinates
int*		pMousePosY			= &mousePosY; // Pointer to computer screen mouse position in Y coordinates

float		angle				= 0.0f; // Angle between mouse position and player

/******************************************************************************/
/*!
	RigidBody and Transform Variables
*/
/******************************************************************************/

RECT		rect; // To get the size of window display


/******************************************************************************/
/*!
	Input Initialization
*/
/******************************************************************************/
void InputInit()
{
	//playerRigidBody = Core::Get().GetComponent<cRigidBody>(playerReference); // 1 = Player Entity
	//playerTransform = Core::Get().GetComponent<cTransform>(playerReference); // 1 = Player Entity

	//playerPosX = playerTransform->position.x; // Player position X
	//playerPosY = playerTransform->position.y; // Player position Y
	//playerVelX = playerRigidBody->velocity.x; // Player velocity X
	//playerVelY = playerRigidBody->velocity.y; // Player velocity Y

	//airResistance = playerRigidBody->inertia; // Air resistance

	GetWindowRect(AESysGetWindowHandle(), &rect); // Size of the windows display
	worldMinX = AEGfxGetWinMinX(); // World minimum X coordinates
	worldMaxX = AEGfxGetWinMaxX(); // World maximum X coordinates
	worldMinY = AEGfxGetWinMinY(); // World minimum Y coordinates 
	worldMaxY = AEGfxGetWinMaxY(); // World maximum Y coordinates

}

/******************************************************************************/
/*!
	Input Update
*/
/******************************************************************************/
void InputUpdate()
{
	
	cRigidBody* playerRigidBody = Core::Get().GetComponent<cRigidBody>(1);
	cTransform* playerTransform = Core::Get().GetComponent<cTransform>(1); // 1 = Player Entity
	cTransform* camTrans = CameraManager::GetCameraTransform();

	AEInputGetCursorPosition(pMousePosX, pMousePosY);
	//printf("mX: %d, mY: %d\n", *pMousePosX, *pMousePosY);

	float windowWidth = rect.right - rect.left;
	float windowHeight = rect.bottom - rect.top;
	//printf("worldMaxX: %f, worldMinX: %f, ", worldMaxX, worldMinX);
	//printf("worldMaxY: %f, worldMinY: %f\n", worldMaxY, worldMinY);

	// Calculate mouse X position in world space
	float screenMousePosX = (static_cast<float>(*pMousePosX) / windowWidth)* (worldMaxX - worldMinX)
		- ((worldMaxX - worldMinX) / 2.0f);



	// Calculate mouse Y position in world space
	float screenMousePosY = -((static_cast<float>(*pMousePosY) / windowHeight)* (worldMaxY - worldMinY)
		- ((worldMaxY - worldMinY) / 2.0f));

	printf("mousePosX = %f, mousePosY = %f \n", screenMousePosX, screenMousePosY);
	//printf("playerPosX = %f, playerPosY = %f", playerTransform->_position.x, playerTransform->_position.y);

	// Angle between mouse and player
	angle = atan2(screenMousePosY, screenMousePosX);

	//printf("mouse pos is %d", *pMousePosX);

	// Set player to point at mouse position
	playerTransform->_rotation = angle;

	if (AEInputCheckCurr(AEVK_UP))
	{
		// Get player direction
		AEVec2 playerDirection;
		// Set Player New Velocity
		AEVec2 playerNewVelocity;
		AEVec2Set(&playerDirection, AECos(playerTransform->_rotation), AESin(playerTransform->_rotation));
		// Player Velocity = direction * flat speed
		AEVec2Scale(&playerNewVelocity, &playerDirection, playerSpeed * g_dt);
		// Add velocity to player
		AEVec2Add(&playerRigidBody->velocityVector, &playerRigidBody->velocityVector, &playerNewVelocity);

		
		//AEVec2 playerSpeed;
		//// Find the velocity according to the acceleration
		//AEVec2Set(&playerSpeed, playerPosX * playerVelX, playerPosY * playerVelY);
		//// Air Resistance
		//AEVec2Set(&playerSpeed, playerSpeed.x * airResistance, playerSpeed.y * airResistance);
		//// Adding the resistance and ship acceleration
		//AEVec2Add(&playerRigidBody->velocity, &playerRigidBody->velocity, &playerSpeed);

		//if (playerVelX >= 200)
		//{
		//	playerVelX = 200; //Limit Speed to 200
		//}

		//if (playerVelY >= 200)
		//{
		//	playerVelY = 200; //Limit Speed to 200
		//}
	}

	if (AEInputCheckCurr(AEVK_DOWN))
	{
		// Get player direction
		AEVec2 playerDirection;
		// Set Player New Velocity
		AEVec2 playerNewVelocity;
		AEVec2Set(&playerDirection, -AECos(playerTransform->_rotation), -AESin(playerTransform->_rotation));
		// Player Velocity = direction * flat speed
		AEVec2Scale(&playerNewVelocity, &playerDirection, playerSpeed * g_dt);
		// Add velocity to player
		AEVec2Add(&playerRigidBody->velocityVector, &playerRigidBody->velocityVector, &playerNewVelocity);

		if (playerVelX >= 200)
		{
			playerVelX = 200; //Limit Speed to 200
		}

		if (playerVelY >= 200)
		{
			playerVelY = 200; //Limit Speed to 200
		}
	}

	if (AEInputCheckCurr(AEVK_RBUTTON))
	{
		AEVec2 thrustDirection;
		AEVec2 thrustVelocity;
		//// Setting the spawning position of the bullet
		//AEVec2Set(&bulletSpeedV, playerPosX * bulletSpeed, playerPosY * bulletSpeed);
		//// Setting the velocity of the bullet
		//AEVec2Add(&bulletRigidBody->velocity, &bulletRigidBody->velocity, &bulletSpeedV);

		playerRigidBody->velocity += playerSpeed;
		if (playerRigidBody->velocity >= 200.0f)
		{
			playerRigidBody->velocity = 200.0f; //Limit Speed to 200
		}

		// Setting the direction of bullet spawn
		AEVec2Set(&thrustDirection, AECos(playerTransform->_rotation), AESin(playerTransform->_rotation));
		// Bullet Speed
		AEVec2Scale(&thrustVelocity, &thrustDirection, 5.0f * g_dt);
		// Add velocity to player
		AEVec2Add(&playerRigidBody->velocityVector, &playerRigidBody->velocityVector, &thrustVelocity);
	}

	//if (AEInputCheckCurr(AEVK_LBUTTON))
	//{
	//	AEVec2 bulletDirection;
	//	AEVec2 bulletVelocity;
	//	//// Setting the spawning position of the bullet
	//	//AEVec2Set(&bulletSpeedV, playerPosX * bulletSpeed, playerPosY * bulletSpeed);
	//	//// Setting the velocity of the bullet
	//	//AEVec2Add(&bulletRigidBody->velocity, &bulletRigidBody->velocity, &bulletSpeedV);

	//	// Setting the direction of bullet spawn
	//	AEVec2Set(&bulletDirection, AECos(playerTransform->rotation), AESin(playerTransform->rotation));
	//	// Bullet Speed
	//	AEVec2Scale(&bulletVelocity, &bulletDirection, 5.0f * g_dt);
	//	// Add velocity to player
	//	AEVec2Add(&bulletRigidBody->velocityVector, &bulletRigidBody->velocityVector, &bulletVelocity);
	//}
}

	

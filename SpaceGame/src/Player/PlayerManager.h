#pragma once
#include "../Global_ECS.h"				//Entity reference
#include "../Components/cRigidBody.h"
#include "../Components/cTransform.h"

namespace PlayerManager
{
	extern ENTITY player;					//Current player must be non-zero to have any control
	
	void Update();
	
	void RotateWithMouse(int mousePosX, int mousePosY, cTransform* camTransform,
		cTransform* playerTransform, cRigidBody* playerRigidBody);

	void ResetPlayer();	
	void PlayerDeath();
}
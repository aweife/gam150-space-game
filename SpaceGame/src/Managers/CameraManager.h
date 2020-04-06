/**********************************************************************************
* \file			CameraManager.h
* \brief		Manage the maths for the camera for the game
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Camera follow
*				- Screen shake
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "../Global_ECS.h"
//All necessary Components Reference
#include "../Components/cTransform.h"
#include "../Components/cCamera.h"
#include "../Components/cRigidBody.h"

namespace CameraManager
{
	void Update();
	void SmoothFollow();
	void StartCameraShake();
	void CameraShake();
	void Update_ScreenShakeTarget();
	cTransform* GetCameraTransform();

	void AssignNewCam(ENTITY currCamera);
	void RemoveCurrCam();
	bool SwitchCam(ENTITY existingCamEntity);
};
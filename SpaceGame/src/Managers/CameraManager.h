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
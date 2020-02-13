#pragma once
#include "../Global_ECS.h"
#include "../Components/cTransform.h"
#include "../Components/cCamera.h"

namespace CameraManager
{


	void AssignNewCam(ENTITY currCamera);
	bool SwitchCam(ENTITY existingCamEntity);

	void Update();
	void SmoothFollow();
	void CameraShake();
};
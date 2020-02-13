#pragma once
#include "../Global_ECS.h"

class CameraManager
{
private:
	unsigned int _cameraCount = 0;
	const unsigned int _cameraMaxCount = 4;
	ENTITY _currCamera = 0;
	ENTITY _sideCamera[3];
public:
	void AssignNewCam(ENTITY currCamera);
	bool SwitchCam(ENTITY existingCamEntity);

	void Update();
	void SmoothFollow();
	void CameraShake();
};
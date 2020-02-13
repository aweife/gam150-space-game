#include "CameraManager.h"
#include "../Components/cTransform.h"
#include "../Components/cCamera.h"
#include "AEGraphics.h"
#include "../ECS/Core.h"

void CameraManager::AssignNewCam(ENTITY currCamera)
{
	AE_ASSERT(_cameraCount < _cameraMaxCount && "Too many camera created.");

	if (_currCamera != 0) //if there is an existing camera
	{
		//Inactive cameras to switch perspective
		_sideCamera[_cameraCount] = _currCamera;
	}
	_currCamera = currCamera;
	++_cameraCount;
}

bool CameraManager::SwitchCam(ENTITY existingCamEntity)
{
	for (unsigned int i = 0; i < _cameraCount; ++i)
	{
		if (existingCamEntity == _sideCamera[i])
		{
			//Switch the camera
			ENTITY tempEntity = _currCamera;
			_currCamera = _sideCamera[i];
			_sideCamera[i] = tempEntity;

			return true; //success
		}
	}
	return false;
}

void CameraManager::Update()
{
	cTransform* currCameraTransform = Core::Get().GetComponent<cTransform>(_currCamera);
	cCamera* currCameraComp = Core::Get().GetComponent<cCamera>(_currCamera);

	AEGfxGetCamPosition(&currCameraTransform->position.x, &currCameraTransform->position.y);
}

void CameraManager::SmoothFollow()
{

}

void CameraManager::CameraShake()
{

}
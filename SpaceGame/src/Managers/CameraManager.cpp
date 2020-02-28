#include "CameraManager.h"						//Self Header
#include "AEEngine.h"							//AE Camera
#include "../ECS/Core.h"						//GetComponent
#include "../Global.h"							//g_dt
#include "../Math/Math.h"						//Smooth Damp




namespace CameraManager
{
	unsigned int _cameraCount = 0;				//Number of loaded camera
	const unsigned int _cameraMaxCount = 4;		//Limit on camera in game
	ENTITY _currCamera = 0;						//ID of current Camera
	ENTITY _sideCamera[3];						//Array of standby camera

	cTransform* currCameraTransform;
	cCamera* currCameraComp;

	void Update()
	{
		if (_currCamera == 0) return;

		SmoothFollow();
		AEGfxSetCamPosition(currCameraTransform->_position.x, currCameraTransform->_position.y);
	}

	void SmoothFollow()
	{
		float capSpeed = currCameraComp->_followSpeed + 10;	//300 + 10

		if (abs(currCameraComp->_followTarget->_position.x - currCameraTransform->_position.x) > /*g_WindowWidth * */0.25f)
		{
			currCameraTransform->_position.x = MBMath_SmoothDamp(currCameraTransform->_position.x, 
				currCameraComp->_followTarget->_position.x, &(currCameraComp->_camVelocityX), 0.8f, capSpeed, g_dt);
		}

		if (abs(currCameraComp->_followTarget->_position.y - currCameraTransform->_position.y) > /*g_WindowHeight * */0.25f)
		{
			currCameraTransform->_position.y = MBMath_SmoothDamp(currCameraTransform->_position.y,
				currCameraComp->_followTarget->_position.y, &(currCameraComp->_camVelocityY), 0.8f, capSpeed, g_dt);
		}
		
	}

	void CameraShake()
	{

	}

	cTransform* GetCameraTransform()
	{
		return currCameraTransform;
	}

	void AssignNewCam(ENTITY currCamera)
	{
		AE_ASSERT(_cameraCount < _cameraMaxCount && "Too many camera created.");

		if (_currCamera != 0)					//if there is an existing camera
		{
			//Inactive cameras to switch perspective
			_sideCamera[_cameraCount] = _currCamera;
		}
		_currCamera = currCamera;
		currCameraTransform = Core::Get().GetComponent<cTransform>(_currCamera);
		currCameraComp = Core::Get().GetComponent<cCamera>(_currCamera);
		++_cameraCount;

	}

	void RemoveCurrCam()
	{
		_currCamera = 0;			//Remove the camera and dont assign a new one
		--_cameraCount; 
		currCameraTransform = nullptr;
		currCameraComp = nullptr;
	}

	bool SwitchCam(ENTITY existingCamEntity)
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
}

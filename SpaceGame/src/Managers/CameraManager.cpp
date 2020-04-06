/**********************************************************************************
* \file			CameraManager.cpp
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

	const float SHAKETHRESHOLD_MIN = 10.0f;
	const float SHAKETHRESHOLD_MAX = 40.0f;
	const float SHAKEDURATION_MIN = 0.5f;
	const float SHAKEDURATION_MAX = 1.0f;
	const float SHAKESPEED_MIN = 0.2f;
	const float SHAKESPEED_MAX = 1.0f;
	float shakeIntensity = 0.0f;

	cTransform* currCameraTransform;
	cCamera* currCameraComp;

	void Update()
	{
		if (_currCamera == 0) return;

		if (currCameraComp->_isdynamic)
		{
			//Apply basic camera follow
			SmoothFollow();

			//Apply secondary camera transformation effects like screenshake...
			if (currCameraComp->_isCameraShake)	CameraShake();

			//Take note that AECam position is not equal to its transform component
			AEGfxSetCamPosition(currCameraTransform->_position.x + currCameraComp->_camOffsetPos.x
				, currCameraTransform->_position.y + currCameraComp->_camOffsetPos.y);
		}
		else
		{
			AEGfxGetCamPosition(&currCameraTransform->_position.x, &currCameraTransform->_position.y);
		}
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

	void StartCameraShake()
	{
		if (!currCameraComp) return;
		
		currCameraComp->_isCameraShake = true;
		currCameraComp->_camEffectStartTime = g_appTime;
		currCameraComp->_camEffectSpeed = AERandFloat() * (SHAKESPEED_MAX - SHAKESPEED_MIN) + SHAKESPEED_MIN;
		currCameraComp->_camEffectDuration = AERandFloat() * (SHAKEDURATION_MAX - SHAKEDURATION_MIN) + SHAKEDURATION_MIN;

		// Set a starting shake intensity (small shake vs a big shake)
		shakeIntensity = AERandFloat() * (SHAKETHRESHOLD_MAX - SHAKETHRESHOLD_MIN) + SHAKETHRESHOLD_MIN;
	}

	void CameraShake()
	{
		if (AEVec2Distance(&currCameraComp->_camOffsetTarget, &currCameraComp->_camOffsetPos) < 1.0f)
		{
			Update_ScreenShakeTarget();
		}
		
		AEVec2 directionVector, distanceVector, tweenVector;
		
		AEVec2Sub(&distanceVector, &currCameraComp->_camOffsetTarget, &currCameraComp->_camOffsetPos);
		AEVec2Scale(&tweenVector, &distanceVector, 0.1f); //Tweening - move 0.1 towards target
		AEVec2Scale(&directionVector, &currCameraComp->_camOffsetTarget, currCameraComp->_camEffectSpeed); //Base speed
		AEVec2Add(&directionVector, &tweenVector, &directionVector);
		if (AEVec2Length(&distanceVector) < AEVec2Length(&directionVector))
		{
			AEVec2Set(&directionVector, distanceVector.x, distanceVector.y);			//Make sure does not exceed target
		}
		AEVec2Add(&currCameraComp->_camOffsetPos, &currCameraComp->_camOffsetPos, &directionVector);

		if (g_appTime - currCameraComp->_camEffectStartTime > currCameraComp->_camEffectDuration)
		{
			currCameraComp->_isCameraShake = false;
			currCameraComp->_camOffsetPos.x = 0;
			currCameraComp->_camOffsetPos.y = 0;
			currCameraComp->_camOffsetTarget.x = 0;
			currCameraComp->_camOffsetTarget.y = 0;
		}
	}

	void Update_ScreenShakeTarget()
	{
		currCameraComp->_camOffsetPos.x = 0;
		currCameraComp->_camOffsetPos.y = 0;

		float currShakeAmount;
		//Range from normalised -1.0f to 1.0f
		currShakeAmount = (AERandFloat() * 2.0f - 1.0f) * shakeIntensity;
		currCameraComp->_camOffsetTarget.x = currShakeAmount;
		currShakeAmount = (AERandFloat() * 2.0f - 1.0f) * shakeIntensity;
		currCameraComp->_camOffsetTarget.y = currShakeAmount;

		shakeIntensity *= 0.9f;			//Intensity will decrease over time non-linearly
	}

	cTransform* GetCameraTransform()
	{
		return currCameraTransform;
	}

	void AssignNewCam(ENTITY currCamera)
	{
		//AE_ASSERT(_cameraCount < _cameraMaxCount - 1 && "Too many camera created.");

		if (_currCamera != 0)		//if there is an existing camera
		{
			//Inactive cameras to switch perspective
			_sideCamera[_cameraCount - 1] = _currCamera;
		}
		_currCamera = currCamera;
		currCameraTransform = Core::Get().GetComponent<cTransform>(_currCamera);
		currCameraComp = Core::Get().GetComponent<cCamera>(_currCamera);
		// Update the camera position without any actual offset
		currCameraComp->_camOffsetPos = { 0 };
		++_cameraCount;

	}

	void RemoveCurrCam()
	{
		_currCamera = 0;			//Remove the camera and dont assign a new one
		_cameraCount = 0; 
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

#include "CameraManager.h"

#include "AEGraphics.h"
#include "../ECS/Core.h"
#include "../Global.h"			//g_dt
#include "../Math/Math.h"

namespace CameraManager
{
	unsigned int _cameraCount = 0;
	const unsigned int _cameraMaxCount = 4;
	ENTITY _currCamera = 0;
	ENTITY _sideCamera[3];

	cTransform* currCameraTransform;
	cCamera* currCameraComp;

	void AssignNewCam(ENTITY currCamera)
	{
		AE_ASSERT(_cameraCount < _cameraMaxCount && "Too many camera created.");

		if (_currCamera != 0) //if there is an existing camera
		{
			//Inactive cameras to switch perspective
			//_sideCamera[_cameraCount] = _currCamera;
		}
		_currCamera = currCamera;
		currCameraTransform = Core::Get().GetComponent<cTransform>(_currCamera);
		currCameraComp = Core::Get().GetComponent<cCamera>(_currCamera);
		++_cameraCount;

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

	void Update()
	{
		if (_currCamera == 0) return;

		SmoothFollow();
		AEGfxSetCamPosition(currCameraTransform->_position.x, currCameraTransform->_position.y);
		//AEGfxSetCamPosition(currCameraComp->_followTarget->_position.x, currCameraComp->_followTarget->_position.y);
		//printf("camPosX = %f, camPosY = %f\n", currCameraTransform->_position.x, currCameraTransform->_position.y);
	}

	void SmoothFollow()
	{
		float boundingX = AEGfxGetWinMaxX() * 2 / 6;
		float boundingY = AEGfxGetWinMaxY() * 3 / 6;


		if (abs(currCameraComp->_followTarget->_position.x - currCameraTransform->_position.x) > boundingX)
		{
			/*currCameraTransform->_position.x = 
				MBMath_Smoothstep(currCameraTransform->_position.x, currCameraComp->_followTarget->_position.x, currCameraComp->_followSpeed * g_dt);*/
			/*currCameraTransform->_position.x =
				MBMath_Lerp(currCameraTransform->_position.x, currCameraComp->_followTarget->_position.x, currCameraComp->_followSpeed * g_dt);*/
			
			currCameraTransform->_position.x = MBMath_SmoothDamp(currCameraTransform->_position.x, 
				currCameraComp->_followTarget->_position.x, &(currCameraComp->_camVelocity), 0.3f, 100.0f, g_dt);

			//printf("%f\n", currCameraTransform->_position.x);
		}
		if (abs(currCameraComp->_followTarget->_position.y - currCameraTransform->_position.y) > boundingY)
		{
			/*currCameraTransform->_position.y = 
				MBMath_Smoothstep(currCameraTransform->_position.y, currCameraComp->_followTarget->_position.y, currCameraComp->_followSpeed * g_dt);*/
			currCameraTransform->_position.y =
				MBMath_Lerp(currCameraTransform->_position.y, currCameraComp->_followTarget->_position.y, currCameraComp->_followSpeed * g_dt);

		}
		
	}

	void CameraShake()
	{

	}

	cTransform* GetCameraTransform()
	{
		return currCameraTransform;
	}
}

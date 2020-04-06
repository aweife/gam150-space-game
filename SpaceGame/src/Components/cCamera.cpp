/*********************************************************************************
* \file			cCamera.cpp
* \brief		Camera Component
* \author		Jun Yi,		Chong,		100% Code Contribution
*
*				Responsible for Camera data
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cCamera.h"

cCamera::cCamera(cTransform* target, float followSpeed, bool dynamic) : _followTarget{ target }, _isdynamic{dynamic}
{
	_name = "cCamera";
	_followSpeed = followSpeed;
}

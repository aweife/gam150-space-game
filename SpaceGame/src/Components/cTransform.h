/**********************************************************************************
* \file			cTransform.h
* \brief		Tranform
* \author		Jun Yi,		Chong,  100% Code Contribution
*
*				Handles the transform component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "AEEngine.h"
#include "Component.h"

class cTransform:public Component
{
public:
	AEMtx33 _transform;
	AEVec2 _position;
	float _rotation;
	AEVec2 _scale;
	
	cTransform();
	cTransform(AEVec2 _position, float _rotation, AEVec2 _scale);
};
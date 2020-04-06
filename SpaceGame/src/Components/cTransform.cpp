/**********************************************************************************
* \file			cTransform.cpp
* \brief		transform
* \author		Jun Yi,		Chong,  100% Code Contribution
*
*				Handles the transform component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cTransform.h"

cTransform::cTransform() : _position{ 0.0f, 0.0f }, _rotation{ 0.0f }, _scale{ 100.0f, 100.0f }, _transform{0} {}

cTransform::cTransform(AEVec2 _position, float _rotation, AEVec2 _scale) 
	: _position{ _position }, _rotation{ _rotation }, _scale{ _scale }, _transform{ 0 }{}
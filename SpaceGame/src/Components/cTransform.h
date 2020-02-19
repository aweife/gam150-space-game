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
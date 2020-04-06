/*********************************************************************************
* \file			cDebugTools.h
* \brief		Debug Tools Component
* \author		Jun Yi,		Chong,		100% Code Contribution
*
*				Responsible for Debug Tools data
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "Component.h"
#include "AEVec2.h"
#include "AEGraphics.h"
#include "../Global.h"				//Default values

enum class DEBUGTYPE
{
	DEBUG_ARROW,
	DEBUG_LINE,
	DEBUG_SQUARE,
	DEBUG_OCTAGON
};

class cDebugTools :public Component
{
public:
	AEVec2& _referencePosition;					//Position of origin
	AEVec2& _referenceEndPosition;				//Position of a optional endpoint
	float& _referenceAngle;						//rotation based on angles
	AEVec2& _referenceRotation;					//rotation based on vectors
	float& _referenceScaleX;					//scale
	float& _referenceScaleY;

	DEBUGTYPE _specifier;
	AEGfxVertexList* _mesh;

	cDebugTools() = delete;					// Constructor
	cDebugTools(AEVec2& pos, AEVec2& rot, float& scaleX, float& scaleY, DEBUGTYPE specifier, const char* meshName, AEVec2& endPos = defaultAEVec2);
	cDebugTools(AEVec2& pos, float& rot, float& scaleX, float& scaleY, DEBUGTYPE specifier, const char* meshName);
	~cDebugTools() = default;				// Virtual Destructor

	void LoadMesh(const char* meshName);
};


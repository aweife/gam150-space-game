/*********************************************************************************
* \file			cDebugTools.cpp
* \brief		Debug Tools Component
* \author		Jun Yi,		Chong,		100% Code Contribution
*
*				Responsible for Debug Tools component
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cDebugTools.h"
#include "../Managers/ResourceManager.h"

cDebugTools::cDebugTools(AEVec2& pos, AEVec2& rot, float& scaleX, float& scaleY, DEBUGTYPE specifier, const char* meshName, AEVec2& endPos)
	:_referencePosition{ pos }, _referenceEndPosition{ endPos }, _referenceRotation{ rot }, _referenceScaleX{ scaleX }, 
	_referenceScaleY{ scaleY }, _specifier{ specifier }, _referenceAngle{ defaultFloat}
{
	LoadMesh(meshName);
}

cDebugTools::cDebugTools(AEVec2& pos, float& rot, float& scaleX, float& scaleY, DEBUGTYPE specifier, const char* meshName)
	:_referencePosition{ pos }, _referenceEndPosition{ defaultAEVec2 }, _referenceRotation{ defaultAEVec2 }, _referenceScaleX{ scaleX },
	_referenceScaleY{ scaleY }, _specifier{ specifier }, _referenceAngle{rot}
{
	LoadMesh(meshName);
}

void cDebugTools::LoadMesh(const char* meshName)
{
	AE_ASSERT_MESG(ResourceManager::meshLibrary.find(meshName) != ResourceManager::meshLibrary.end(), "Failed to find Mesh!");

	_mesh = ResourceManager::meshLibrary[meshName];
}
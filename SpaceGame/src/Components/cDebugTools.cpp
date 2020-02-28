#include "cDebugTools.h"
#include "../Managers/ResourceManager.h"

cDebugTools::cDebugTools(AEVec2& pos, AEVec2& rot, float& scale, DEBUGTYPE specifier, const char* meshName)
	:_referencePosition{ pos }, _referenceRotation{ rot }, _referenceScale{ scale }, _specifier{ specifier }
{
	LoadMesh(meshName);
}

void cDebugTools::LoadMesh(const char* meshName)
{
	AE_ASSERT_MESG(ResourceManager::meshLibrary.find(meshName) != ResourceManager::meshLibrary.end(), "Failed to find Mesh!");

	_mesh = ResourceManager::meshLibrary[meshName];
}
#pragma once

#include "Component.h"
#include "AEVec2.h"
#include "AEGraphics.h"

enum class DEBUGTYPE
{
	DEBUG_ARROW
};

class cDebugTools :public Component
{

public:
	AEVec2& _referencePosition;
	AEVec2& _referenceRotation;
	float& _referenceScale;
	DEBUGTYPE _specifier;
	AEGfxVertexList* _mesh;

	cDebugTools() = delete;					// Constructor
	cDebugTools(AEVec2& pos, AEVec2& rot, float& scale, DEBUGTYPE specifier, const char* meshName);
	~cDebugTools() = default;				// Virtual Destructor

	void LoadMesh(const char* meshName);
};


#pragma once

#include "AEEngine.h"					//reference to AEGfxVertexList
#include "Component.h"					//Base Class

struct cSprite :public Component
{
public:
	AEGfxVertexList* _mesh;

	cSprite(ENTITY parent);		// Constructor with parameter
	virtual ~cSprite();			// Virtual Destructor

	virtual void Init();
};
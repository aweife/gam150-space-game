#pragma once

#include "AEEngine.h"					//reference to AEGfxVertexList
#include "Component.h"

class SpriteComponent :public Component
{
public:
	AEGfxVertexList* _mesh;

	SpriteComponent(ENTITYID parent);				// Default Constructor
	virtual ~SpriteComponent();		// Virtual Destructor

	virtual void Init();
};
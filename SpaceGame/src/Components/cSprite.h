#pragma once

#include "AEEngine.h"					//reference to AEGfxVertexList
#include "Component.h"					//Base Class

struct cSprite :public Component
{
public:
	//Data
	AEGfxVertexList* _mesh;

	//Functions
	cSprite(ENTITY parent);		// Constructor with parameter
	virtual ~cSprite();			// Virtual Destructor

	void Init() override;
};


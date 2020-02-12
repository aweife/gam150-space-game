#pragma once

#include "AEEngine.h"					//reference to AEGfxVertexList
#include "Component.h"					//Base Class

class cSprite :public Component
{
public:
	//Data
	AEGfxVertexList* _mesh;

	AEGfxTexture* texture;

	cSprite(ENTITY parent);							// Constructor with parameter
	cSprite(ENTITY parent, const char* texture);	// To be changeds
	~cSprite();										// Virtual Destructor

	void Init();
	void LoadTexture(const char* pathName);
};
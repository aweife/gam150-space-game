#pragma once

#include "AEEngine.h"					//reference to AEGfxVertexList
#include "Component.h"					//Base Class

class cSprite :public Component
{
public:
	//Data
	AEGfxVertexList* _mesh;
	AEGfxTexture* _texture;
	unsigned int _layer; /*0 to 5...see render system*/


	cSprite(ENTITY parent, const char* texture, unsigned int layer = 0);	// Constructor with parameter
	~cSprite();										// Virtual Destructor

	void Init();
	void LoadTexture(const char* pathName);
};
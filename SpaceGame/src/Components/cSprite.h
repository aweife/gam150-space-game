/**********************************************************************************
* \file			cSprite.h
* \brief		Sprite
* \author		Jun Yi,		Chong,  50% Code Contribution
*				Wei Feng,	  Ang,  50% Code Contribution
*
*				Handles the sprite component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "AEEngine.h"					//reference to AEGfxVertexList
#include "Component.h"					//Base Class
#include "../Global_Graphics.h"			//ColorInfo

class cSprite :public Component
{
public:
	//Data
	AEGfxVertexList* _mesh;
	AEGfxTexture*	_texture;
	unsigned int	_layer;				/*0 to 5...see render system*/
	ColorInfo		_colorTint = {1.0f, 1.0f, 1.0f, 1.0f};				//tint or base color
	ColorInfo		_colorBlend = { 0.0f, 0.0f, 0.0f, 0.0f };			//tint or base color
	SPRITE_RM		_mode;

	//Additional modifiers
	AEVec2			_UVOffset;
	AEGfxBlendMode	_blend;

	// Constructor with parameter
	cSprite(ENTITY parent, const char* meshName, const char* textureName, unsigned int layer  = 0, 
		SPRITE_RM mode = SPRITE_RM::RM_SPRITE);	
	~cSprite() = default;										// Virtual Destructor...memory clean up by unique_ptr

	void LoadMesh(const char* meshName);
	void LoadTexture(const char* textureName);
};
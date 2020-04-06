/**********************************************************************************
* \file			cSprite.cpp
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
#include "cSprite.h"			//Self Header
#include "../Managers/ResourceManager.h"


cSprite::cSprite(ENTITY parent, const char* meshName, const char* textureName, unsigned int layer, SPRITE_RM mode)
	:_mesh{ nullptr }, _layer{ layer }, _mode{ mode }, _UVOffset{0,0}, _blend{ AEGfxBlendMode::AE_GFX_BM_BLEND }
{
	//Base Component Variables
	_name = "class SpriteComponent";	
	_componentID = ID_SpriteComponent;
	_entityParent = parent;

	LoadMesh(meshName);					
	if (strcmp(textureName, "None") != 0) LoadTexture(textureName);
}

void cSprite::LoadMesh(const char* meshName)
{
	AE_ASSERT_MESG(ResourceManager::meshLibrary.find(meshName) != ResourceManager::meshLibrary.end(), "Failed to find Mesh!");
		
	_mesh = ResourceManager::meshLibrary[meshName];
}

void cSprite::LoadTexture(const char* textureName)
{
	AE_ASSERT_MESG(ResourceManager::textureLibrary.find(textureName) != ResourceManager::textureLibrary.end(), "Failed to find Texture!");

	_texture = ResourceManager::textureLibrary[textureName];
}

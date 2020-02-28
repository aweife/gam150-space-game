/******************************************************************************
* \file			cSprite.cpp
* \author		Chong Jun Yi, Ang Wei Feng
* \version		1.1
* \date			2/01/2020
* \par			Component 
* \note			Course: GAM150
* \brief		Component for a 2D sprite
				- Mesh
				- Texture
				- Tint and Color
				- Transparency

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "cSprite.h"			//Self Header
#include "../Tools/Console.h"	//remove after testing
#include "../Managers/ResourceManager.h"

cSprite::cSprite(ENTITY parent, const char* meshName, const char* textureName, unsigned int layer)
{
	//Common Component variables
	_name = "class SpriteComponent";	//Do not change this otherwise remove component wont work
	//_categor = SYS_GRAPHICS;			//not sure why have warning here
	_componentID = ID_SpriteComponent;
	_entityParent = parent;

	//Component Specific variables
	_mesh = nullptr;
	_layer = layer;

	Console_Cout("Creating SpriteComponent...");
	LoadMesh(meshName);					
	LoadTexture(textureName);	
}

cSprite::~cSprite()
{
	//AEGfxMeshFree(_mesh);		//2 memory leaks if not done
	//if (_texture)
	//	AEGfxTextureUnload(_texture);
	Console_Cout("SpriteComponent Destructor");
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

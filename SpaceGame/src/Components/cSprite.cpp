/*********************************************************************************
* \file			cSprite.cpp
* \author		Chong Jun Yi, Ang Wei Feng
* \version		1.1
* \date			2/01/2019
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
**********************************************************************************/
#include "cSprite.h"			//Self Header

#include "../Tools/Console.h"	//remove after testing

cSprite::cSprite(ENTITY parent)
{
	//Common Component variables
	_name = "class SpriteComponent";				//Do not change this otherwise remove component wont work
	//_category = SYS_GRAPHICS;						//not sure why have warning here
	_componentID = ID_SpriteComponent;	
	_entityParent = parent;

	//Component Specific variables
	_mesh = nullptr;

	//Create mesh
	Init();
}

cSprite::~cSprite()
{
	AEGfxMeshFree(_mesh);		//2 memory leaks if not done
	Console_Cout("SpriteComponent Destructor");
}

void cSprite::Init()
{
	Console_Cout("SpriteComponent Init");

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
		30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
		30.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in _mesh
	_mesh = AEGfxMeshEnd();

	AE_ASSERT_MESG(_mesh, "Failed to create mesh!");
}
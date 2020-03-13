/**********************************************************************************
* \file			ResourceManager.h
* \brief		Manages loading of assets such as mesh, texture, sound
* \author		Jun Yi, Chong, 100% Code Contribution
*
*				Long Description
*				- Allocates memory for mesh and texture under AEEngine
*				- Breaks up the loading across each frame so game will not freeze
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "AEEngine.h"
#include <unordered_map>


namespace ResourceManager
{
	extern std::unordered_map<const char*, AEGfxVertexList*> meshLibrary;
	extern std::unordered_map<const char*, AEGfxTexture*> textureLibrary;
	extern u32 fontId;
	extern bool loadingCompleted;
	extern unsigned int loadingProgress;

	void Init();
	void Update(unsigned int loadingCode);

	void GenerateMeshLibrary_Essentials();
	void GenerateMeshLibrary_1();

	void LoadTextureLibrary_Essential();
	void LoadTextureLibrary_1(unsigned int* stage, unsigned int* progress);

	void Unload();

}
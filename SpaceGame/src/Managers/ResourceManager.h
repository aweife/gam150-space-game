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
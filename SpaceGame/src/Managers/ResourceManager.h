#pragma once
#include "AEEngine.h"
#include <unordered_map>


namespace ResourceManager
{
	extern std::unordered_map<const char*, AEGfxVertexList*> meshLibrary;
	extern std::unordered_map<const char*, AEGfxTexture*> textureLibrary;
	extern u32 fontId;
	extern bool loadingCompelete;
	extern unsigned int loadingProgress;

	void Init();

	void Update(unsigned int loadingCode);

	void GenerateMeshLibrary();

	void LoadTextureLibrary_Essential();

	void LoadTextureLibrary_1(unsigned int* stage, unsigned int* progress);

	void Unload();

}
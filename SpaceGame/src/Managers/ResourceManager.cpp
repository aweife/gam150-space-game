#include "ResourceManager.h"
#include "GameStateManager.h"
#include "../Global.h"					//app time

#include "../Tools/Console.h"

namespace ResourceManager
{
	std::unordered_map<const char*, AEGfxVertexList*> meshLibrary;
	std::unordered_map<const char*, AEGfxTexture*> textureLibrary;
	bool loadingCompelete = true;
	unsigned int loadingProgress = 100;
	unsigned int loadingStage = 0;
	u32 fontId = 0;

	void Init()					//Run at start of game
	{
		fontId = AEGfxCreateFont("Courier New", 24, true, false);
		GenerateMeshLibrary();
		LoadTextureLibrary_Essential();
	}

	void Update(unsigned int loadingCode)
	{
		switch (loadingCode)
		{
		case GS_LEVEL1:
			LoadTextureLibrary_1(&loadingStage, &loadingProgress);
			break;
		default:
			break;
		}
	}

	void GenerateMeshLibrary()
	{
		AEGfxVertexList* mesh;

		// -----------------------------------------------------------------------
		// Square Mesh
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,				// 3
			0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,				//
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);				// 1		2
		AEGfxTriAdd(											//
			0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,				// 3        2
			0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,					//
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);				//          1

		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "Square Mesh", mesh });

		// -----------------------------------------------------------------------
		// Arrow Line Mesh
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);			 /*		   3\			*/
		AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);			 /*		1----25 		*/
		AEGfxVertexAdd(0.8f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);			 /*		   4/			*/
		AEGfxVertexAdd(0.8f, -0.2f, 0xFFFFFFFF, 0.0f, 0.0f);		 /*						*/
		AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);

		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({"Arrow Line", mesh});

	}

	void LoadTextureLibrary_Essential()
	{
		//SHOULD BE AS LIGHT WEIGHT AS POSSIBLE
		textureLibrary.insert({"BG_Loading", AEGfxTextureLoad("res/Loading.png") });
	}

	void LoadTextureLibrary_1(unsigned int* stage, unsigned int * progress)
	{
		f64 currTime, startTime;
		AEGetTime(&currTime);
		AEGetTime(&startTime);

		while (currTime - startTime < 1.0f/60.0f && *progress < 100)
		{
			switch (*stage)
			{
				case 0:
					if (textureLibrary.find("Player_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Player_1", AEGfxTextureLoad("res/Player_MachineGun.png") });
					break;
				case 1:
					if (textureLibrary.find("Enemy_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Enemy_1", AEGfxTextureLoad("res/Enemy_1.png") });
					break;
				case 2:
					if (textureLibrary.find("Planet_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_1", AEGfxTextureLoad("res/Prop_Planet1.png") });
					break;
				case 3:
					if (textureLibrary.find("Planet_2") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_2", AEGfxTextureLoad("res/Prop_Planet2.png") });
					break;
				case 4:
					if (textureLibrary.find("Planet_3") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_3", AEGfxTextureLoad("res/Prop_Planet3.png") });
					break;
				case 5:
					if (textureLibrary.find("Planet_4") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_4", AEGfxTextureLoad("res/Prop_Planet4.png") });
					break;
				case 6:
					if (textureLibrary.find("Bullet_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Bullet_1", AEGfxTextureLoad("res/Weapon_Bullet1.png") });
					break;
				case 7:
					if (textureLibrary.find("BG_1") != textureLibrary.end()) break;
					//textureLibrary.insert({ "BG_1", AEGfxTextureLoad("res/BG_Background1.png") });
					*progress = 100;
					break;
			}
			*progress += static_cast<unsigned int>(100 / 8);
			Console_Cout("Loading process", static_cast<int>(*progress));
			++*stage;
			AEGetTime(&currTime);
		}
	}

	void Unload()
	{
		AEGfxDestroyFont(fontId);
		for (auto const& resource : meshLibrary)
		{
			AEGfxMeshFree(resource.second);
		}
		for (auto const& resource : textureLibrary)
		{
			AEGfxTextureUnload(resource.second);
		}
	}
}
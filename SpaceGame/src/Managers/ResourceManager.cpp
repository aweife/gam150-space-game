#include "ResourceManager.h"			// Function Declaration
#include "GameStateManager.h"			// Load for different game state levels
#include "../Global.h"					// app time

#include "../Tools/Console.h"

namespace ResourceManager
{
	//Resource Related Storage
	std::unordered_map<const char*, AEGfxVertexList*> meshLibrary;
	std::unordered_map<const char*, AEGfxTexture*> textureLibrary;
	u32 fontId = 0;

	//Progress Tracker Variables
	bool loadingCompleted = true;						//Is the Jobs done?
	unsigned int loadingProgress = 100;					//Represents Percentage
	unsigned int loadingStage = 0;						//Represents Number of Items to load
	

	void Init()					//Runs at start of game
	{
		fontId = AEGfxCreateFont("Tahoma", 24, true, false);
		GenerateMeshLibrary_1();							//CHANGE THIS to essentials !!!!
		LoadTextureLibrary_Essential();
	}

	void Update(unsigned int loadingCode)
	{
		switch (loadingCode)
		{
		case GS_MAINMENU:
			break;
		case GS_LEVEL1:
			LoadTextureLibrary_1(&loadingStage, &loadingProgress);
			break;
		default:
			break;
		}
	}

	void GenerateMeshLibrary_Essentials()
	{

	}

	void GenerateMeshLibrary_1()
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
		// Octagon Mesh
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//2-3 o CLOCK triangle
			0.5f, 0.0f, 0xFFFF0000, 1.0f, 0.5f,
			0.353553f, 0.353553f, 0xFFFF0000, 0.853553f, 0.853553f);
		AEGfxTriAdd(											
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//12-1 o CLOCK triangle
			0.353553f, 0.353553f, 0xFFFF0000, 0.853553f, 0.853553f,
			0.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f);	
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//11-12 o CLOCK triangle
			0.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f,
			-0.353553f, 0.353553f, 0xFFFFFFFF, 0.146446f, 0.853553f);
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//9-10 o CLOCK triangle
			-0.353553f, 0.353553f, 0xFFFFFFFF, 0.146446f, 0.853553f,
			-0.5f, 0.0f, 0xFFFFFFFF, 0, 0.5f);
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//8-9 o CLOCK triangle
			-0.5f, 0.0f, 0xFFFFFFFF, 0, 0.5f,
			-0.353553f, -0.353553f, 0xFFFFFFFF, 0.146446f, 0.146446f);
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//6-7 o CLOCK triangle
			-0.353553f, -0.353553f, 0xFFFFFFFF, 0.146446f, 0.146446f,
			0.0, -0.5f, 0xFFFFFFFF, 0.5f, 0.0f);
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//5-6 o CLOCK triangle
			0.0, -0.5f, 0xFFFFFFFF, 0.5f, 0.0f,
			0.353553f, -0.353553f, 0xFFFFFFFF, 0.853553f, 0.146446f);
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFF0000, 0.5f, 0.5f,					//4-3 o CLOCK triangle
			0.353553f, -0.353553f, 0xFFFFFFFF, 0.853553f, 0.146446f,
			0.5f, 0.0f, 0xFFFF0000, 1.0f, 0.5f);


		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");
		meshLibrary.insert({ "Octagon Mesh", mesh });

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

		// Saving the mesh (list of vertex) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");
		meshLibrary.insert({"Arrow Line", mesh});

		// -----------------------------------------------------------------------
		// Simple Line Mesh
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);			 /*		   			*/
		AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);			 /*		1----2 		*/

		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "Simple Line", mesh });

		// -----------------------------------------------------------------------
		// Square Frame
		// -----------------------------------------------------------------------
		AEGfxMeshStart();
		
		// This shape has 2 triangles
		AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);			/*		   			*/
		AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);			/*		4----3 		*/
		AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);				/*		|    |		*/
		AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);			/*		1----2		*/
		AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);			/*		5	 		*/

		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "Square Frame", mesh });

		// -----------------------------------------------------------------------
		// Octagon Frame
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxVertexAdd(0.5f, 0.0f, 0xFFFFFFFF, 1.0f, 0.5f);
		AEGfxVertexAdd(0.353553f, 0.353553f, 0xFFFFFFFF, 0.853553f, 0.853553f);
		AEGfxVertexAdd(0.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f);
		AEGfxVertexAdd(-0.353553f, 0.353553f, 0xFFFFFFFF, 0.146446f, 0.853553f);
		AEGfxVertexAdd(-0.5f, 0.0f, 0xFFFFFFFF, 0, 0.5f);
		AEGfxVertexAdd(-0.353553f, -0.353553f, 0xFFFFFFFF, 0.146446f, 0.146446f);
		AEGfxVertexAdd(0.0, -0.5f, 0xFFFFFFFF, 0.5f, 0.0f);// Saving the mesh (list of triangles) in mesh
		AEGfxVertexAdd(0.353553f, -0.353553f, 0xFFFFFFFF, 0.853553f, 0.146446f); 
		AEGfxVertexAdd(0.5f, 0.0f, 0xFFFFFFFF, 1.0f, 0.5f);
		
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "Octagon Frame", mesh });

		// -----------------------------------------------------------------------
		// UI - HP Bar 
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		AEGfxTriAdd(
			0.0f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
			0.8f, -0.5f, 0xFFFF0000, 0.5f, 0.0f,
			1.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f);
		AEGfxTriAdd(
			1.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f,
			0.2f, 0.5f, 0xFFFF0000, 0.0f, 1.0f,
			0.0f, -0.5f, 0xFFFF0000, 0.0f, 0.0f);

		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "UI_HP bar", mesh });
	}

	void LoadTextureLibrary_Essential()
	{
		//SHOULD BE AS LIGHT WEIGHT AS POSSIBLE
		textureLibrary.insert({"GameLogo", AEGfxTextureLoad("res/GameLogo.png") });
		textureLibrary.insert({"BG_MainMenu", AEGfxTextureLoad("res/Loading.png") });

		//not very impt...
		textureLibrary.insert({ "Texture_Default", AEGfxTextureLoad("res/Texture_Default.png") });
		textureLibrary.insert({ "Texture_Fill", AEGfxTextureLoad("res/Texture_Fill.png") });
		textureLibrary.insert({ "Texture_Fill2", AEGfxTextureLoad("res/Texture_Fill2.png") });
		textureLibrary.insert({ "HP_FILL", AEGfxTextureLoad("res/HP_Fill.png") });
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
					textureLibrary.insert({ "BG_1", AEGfxTextureLoad("res/BG_Space1.png") });
					break;
				case 8:
					if (textureLibrary.find("Particle_Default") != textureLibrary.end()) break;
					textureLibrary.insert({ "Particle_Default", AEGfxTextureLoad("res/Particle_Default.png") });
					*progress = 100;
					break;
			}
			*progress += static_cast<unsigned int>(100 / 9);
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
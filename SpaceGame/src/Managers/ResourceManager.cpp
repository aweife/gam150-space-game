/**********************************************************************************
* \file			ResourceManager.cpp
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
#include "ResourceManager.h"			// Function Declaration
#include "GameStateManager.h"			// Load for different game state levels
#include "../Global.h"					// app time

#include "../Tools/Console.h"			// Testing 

namespace ResourceManager
{
	//Resource Related Storage
	std::unordered_map<const char*, AEGfxVertexList*> meshLibrary;
	std::unordered_map<const char*, AEGfxTexture*> textureLibrary;
	u32 fontId = 0;

	//Progress Tracker Variables
	bool loadingCompleted = true;						//Is the loading done?
	unsigned int loadingProgress = 100;					//Represents Percentage
	unsigned int loadingStage = 0;						//Represents Number of Items to load
	

	//Runs at start of game
	void Init()					
	{
		fontId = AEGfxCreateFont("Tahoma", 24, true, false);
		GenerateMeshLibrary_Essentials();				//CHANGE THIS to essentials !!!!
		LoadTextureLibrary_Essential();
	}

	void Update(unsigned int loadingCode)
	{
		// loadingCode represents loading for different levels or stages of the game
		switch (loadingCode)
		{
		case GS_MAINMENU:
			break;
		case GS_LEVEL1:
			GenerateMeshLibrary_1();
			LoadTextureLibrary_1(&loadingStage, &loadingProgress);
			break;
		default:
			break;
		}
	}

	void GenerateMeshLibrary_Essentials()
	{
		//Check if loaded this function before
		if (meshLibrary.find("Square Mesh") != meshLibrary.end()) return;


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
	}

	void GenerateMeshLibrary_1()
	{
		if (meshLibrary.find("Square Mesh2") != meshLibrary.end()) return;
		AEGfxVertexList* mesh;

		// -----------------------------------------------------------------------
		// Square Mesh half UV
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.5f,				// 3
			0.5f, -0.5f, 0xFFFF0000, 1.0f, 0.5f,				//
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);				// 1		2
		AEGfxTriAdd(											//
			0.5f, -0.5f, 0xFFFF0000, 1.0f, 0.5f,				// 3        2
			0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,					//
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);				//          1

		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");
		meshLibrary.insert({ "Square Mesh2", mesh });

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
		AEGfxVertexAdd(0.0, -0.5f, 0xFFFFFFFF, 0.5f, 0.0f);
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
			0.0f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,		//Slanted Parallelogram
			0.8f, -0.5f, 0xFFFF0000, 0.5f, 0.0f,
			1.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f);
		AEGfxTriAdd(
			1.0f, 0.5f, 0xFFFFFFFF, 0.5f, 1.0f,
			0.2f, 0.5f, 0xFFFF0000, 0.0f, 1.0f,
			0.0f, -0.5f, 0xFFFF0000, 0.0f, 0.0f);

		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "UI_HP bar", mesh });

		// -----------------------------------------------------------------------
		// UI - Thruster Overheat
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		//modifiables
		float segments = 7.0f;
		float innerRadius = 10.001f;			//not sure why it has a limit...
		float circularRange = PI * 2 * 24 / 36;			//300 degree

		//Do not modify	
		float deltaAngle = circularRange / segments;
		//float offset = 0.25f * deltaAngle /2;			//offset due to gap between segements
		float startAngle = 2*PI * (180/360.0f) /*- offset*/;		// PI /2 + circularRange/2 - offset; //balanced alighnment
		for (int i = 0; i < segments; ++i)
		{
			AEGfxTriAdd(								
				innerRadius*cos(startAngle - (i * deltaAngle)), innerRadius * sin(startAngle - (i * deltaAngle))
				,0xFFFF0000, 1.0f, i /segments * 0.25f,		
				innerRadius * cos(startAngle - ((i + 0.75f) * deltaAngle)), innerRadius * sin(startAngle - ((i + 0.75f) * deltaAngle))
				, 0xFFFFFFFF, 1.0f, (i + 0.75f) / segments * 0.25f,
				50.0f * cos(startAngle - ((i + 0.75f) * deltaAngle)), 50.0f * sin(startAngle - ((i + 0.75f) * deltaAngle))
				, 0xFFFFFFFF, 0.0f, (i + 0.75f) / segments * 0.25f);
			AEGfxTriAdd(								//8-9 o CLOCK triangle
				50.0f * cos(startAngle - ((i + 0.75f) * deltaAngle)), 50.0f * sin(startAngle - ((i + 0.75f) * deltaAngle))
				, 0xFFFFFFFF, 0.0f, (i + 0.75f) / segments * 0.25f,
				50.0f * cos(startAngle - (i * deltaAngle)), 50.0f * sin(startAngle -( i * deltaAngle))
				, 0xFFFF0000, 0.0f, i / segments * 0.25f,
				innerRadius * cos(startAngle - (i * deltaAngle)), innerRadius * sin(startAngle - (i * deltaAngle))
				, 0xFFFF0000, 1.0f, i / segments * 0.25f);
		}
		

		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "UI_Thruster", mesh });

	}

	void LoadTextureLibrary_Essential()
	{
		//SHOULD BE AS LIGHT WEIGHT AS POSSIBLE
		if (textureLibrary.find("GameLogo") == textureLibrary.end())
		{
			textureLibrary.insert({ "GameLogo", AEGfxTextureLoad("res/GameLogo.png") });
		}	
		if (textureLibrary.find("BG_MainMenu") == textureLibrary.end())
		{
			textureLibrary.insert({ "BG_MainMenu", AEGfxTextureLoad("res/Loading.png") });
		}
		if (textureLibrary.find("Texture_Default") == textureLibrary.end())
		{
			textureLibrary.insert({ "Texture_Default", AEGfxTextureLoad("res/Texture_Default.png") });
		}
		if (textureLibrary.find("Particle_Default") == textureLibrary.end())
		{
			textureLibrary.insert({ "Particle_Default", AEGfxTextureLoad("res/Particle_Default.png") });
		}
		if (textureLibrary.find("Player_1") == textureLibrary.end())
		{
			textureLibrary.insert({ "Player_1", AEGfxTextureLoad("res/Player_MachineGun.png") });
		}
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
					if (textureLibrary.find("Player_Shield") != textureLibrary.end()) break;
					textureLibrary.insert({"Player_Shield", AEGfxTextureLoad("res/Player_Shield.png") });
					break;
				case 1:
					if (textureLibrary.find("Enemy_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Enemy_1", AEGfxTextureLoad("res/Enemy_1.png") });
					break;
				case 2:
					if (textureLibrary.find("Enemy_2") != textureLibrary.end()) break;
					textureLibrary.insert({ "Enemy_2", AEGfxTextureLoad("res/Enemy_2.png") });
					break;
				case 3:
					if (textureLibrary.find("Planet_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_1", AEGfxTextureLoad("res/Prop_Planet1.png") });
					break;
				case 4:
					if (textureLibrary.find("Planet_2") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_2", AEGfxTextureLoad("res/Prop_Planet2.png") });
					break;
				case 5:
					if (textureLibrary.find("Planet_3") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_3", AEGfxTextureLoad("res/Prop_Planet3.png") });
					break;
				case 6:
					if (textureLibrary.find("Planet_4") != textureLibrary.end()) break;
					textureLibrary.insert({"Planet_4", AEGfxTextureLoad("res/Prop_Planet4.png") });
					break;
				case 7:
					if (textureLibrary.find("Bullet_1") != textureLibrary.end()) break;
					textureLibrary.insert({"Bullet_1", AEGfxTextureLoad("res/Weapon_Bullet1.png") });
					break;
				case 8:
					if (textureLibrary.find("BG_1") != textureLibrary.end()) break;
					textureLibrary.insert({ "BG_1", AEGfxTextureLoad("res/BG_Space1.png") });
					break;
				case 9:
					if (textureLibrary.find("Random_Upgrade") != textureLibrary.end()) break;
					textureLibrary.insert({ "Random_Upgrade", AEGfxTextureLoad("res/QuestionMarkPlacehold.png") });
					break;
				case 10:
					if (textureLibrary.find("Upgrade_1") != textureLibrary.end()) break;
					textureLibrary.insert({ "Upgrade_1", AEGfxTextureLoad("res/UpgradePlacehold.png") });
					break;
				case 11:
					if (textureLibrary.find("AI_Indicator") != textureLibrary.end()) break;
					textureLibrary.insert({ "AI_Indicator", AEGfxTextureLoad("res/AI_Indicator.png") });
					break;
				case 12:
					if (textureLibrary.find("HP_FILL") != textureLibrary.end()) break;
					textureLibrary.insert({ "HP_FILL", AEGfxTextureLoad("res/HP_Fill.png") });
					break;
				case 13:
					if (textureLibrary.find("Texture_Fill") != textureLibrary.end()) break;
					textureLibrary.insert({ "Texture_Fill", AEGfxTextureLoad("res/Texture_Fill.png") });
					break;
				case 14:
					if (textureLibrary.find("Texture_Fill2") != textureLibrary.end()) break;
					textureLibrary.insert({ "Texture_Fill2", AEGfxTextureLoad("res/Texture_Fill2.png") });
					break;
				case 15:
					if (textureLibrary.find("Texture_Fill3") != textureLibrary.end()) break;
					textureLibrary.insert({ "Texture_Fill3", AEGfxTextureLoad("res/Texture_Fill3.png") });
					*progress = 100;
					break;
			}
			*progress < 100? *progress += static_cast<unsigned int>(100 / 16): *progress = 100;
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
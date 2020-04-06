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
			//nothing to load
			loadingProgress = 100;
			break;
		case GS_LEVEL1:
			GenerateMeshLibrary_1();
			LoadTextureLibrary_1(&loadingStage, &loadingProgress);
			break;
		case GS_UPGRADE:
			//nothing to load
			loadingProgress = 100;
			break;
		case GS_LEVEL2:
			LoadTextureLibrary_2(&loadingStage, &loadingProgress);
			break;
		case GS_LEVEL3:
			//nothing to load
			GenerateMeshLibrary_1();
			LoadTextureLibrary_1(&loadingStage, &loadingProgress);
			//loadingProgress = 100;
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
		// Circle Mesh
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		//Creating the ball shape
		int Parts = 12;
		for (float i = 0; i < Parts; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
				cosf(i * 2 * PI / Parts) * 1.0f, sinf(i * 2 * PI / Parts) * 1.0f, 0xFFFFFF00, 0.0f, 0.0f,
				cosf((i + 1) * 2 * PI / Parts) * 1.0f, sinf((i + 1) * 2 * PI / Parts) * 1.0f, 0xFFFFFF00, 0.0f, 0.0f);
		}
		// Saving the mesh (list of triangles) in mesh
		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");
		meshLibrary.insert({ "Circle Mesh", mesh });

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
		// Bullet - Laser
		// -----------------------------------------------------------------------
		AEGfxMeshStart();

		AEGfxTriAdd(
			1.0f, -1.0f, 0xFFFF0000, 0.5f, 0.0f,				// 3
			0.0f, -1.0f, 0xFFFF0000, 0.0f, 0.0f,				//
			1.0f, 1.0f, 0xFFFFFFFF, 0.5f, 1.0f);				// 1		2
		AEGfxTriAdd(											//
			0.0f, -1.0f, 0xFFFF0000, 0.0f, 0.0f,				// 3        2
			0.0f, 1.0f, 0xFFFF0000, 0.0f, 1.0f,					//
			1.0f, 1.0f, 0xFFFFFFFF, 0.5f, 1.0f);				//          1

		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "LaserBeam", mesh });


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
		float segments = 8.0f;
		float innerRadius = 0.2f;			//not sure why it has a limit...
		float circularRange = PI * 2 * 25 / 36;			//300 degree

		//Do not modify	
		float deltaAngle = circularRange / segments;
		//float offset = 0.25f * deltaAngle /2;			//offset due to gap between segements
		float startAngle = 2*PI * (180/360.0f) /*- offset*/;		// PI /2 + circularRange/2 - offset; //balanced alighnment
		for (int i = 0; i < segments; ++i)
		{
			AEGfxTriAdd(								
				innerRadius*cos(startAngle - (i * deltaAngle)), innerRadius * sin(startAngle - (i * deltaAngle))
				,0xFFFF0000, 1.0f, i /segments * 0.5f,		
				innerRadius * cos(startAngle - ((i + 0.8f) * deltaAngle)), innerRadius * sin(startAngle - ((i + 0.8f) * deltaAngle))
				, 0xFFFFFFFF, 1.0f, (i + 1.0f) / segments * 0.5f,
				1.0f * cos(startAngle - ((i + 0.8f) * deltaAngle)), 1.0f * sin(startAngle - ((i + 0.8f) * deltaAngle))
				, 0xFFFFFFFF, 0.0f, (i + 1.0f) / segments * 0.5f);
			AEGfxTriAdd(								//8-9 o CLOCK triangle
				1.0f * cos(startAngle - ((i + 0.8f) * deltaAngle)), 1.0f * sin(startAngle - ((i + 0.8f) * deltaAngle))
				, 0xFFFFFFFF, 0.0f, (i + 1.0f) / segments * 0.5f,
				1.0f * cos(startAngle - (i * deltaAngle)), 1.0f * sin(startAngle -( i * deltaAngle))
				, 0xFFFF0000, 0.0f, i / segments * 0.5f,
				innerRadius * cos(startAngle - (i * deltaAngle)), innerRadius * sin(startAngle - (i * deltaAngle))
				, 0xFFFF0000, 1.0f, i / segments * 0.5f);
		}
		

		mesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(mesh, "Failed to create mesh!");

		meshLibrary.insert({ "UI_Thruster", mesh });

	}

	void LoadTextureLibrary_Essential()
	{
		//SHOULD BE AS LIGHT WEIGHT AS POSSIBLE
		if (textureLibrary.find("DigiPenLogo") == textureLibrary.end())
		{
			textureLibrary.insert({"DigiPenLogo", AEGfxTextureLoad("res/DigiPen_Singapore_WEB_RED.png") });
		}
		if (textureLibrary.find("TeamLogo") == textureLibrary.end())
		{
			textureLibrary.insert({ "TeamLogo", AEGfxTextureLoad("res/MoonBase_Logo.png") });
		}
		if (textureLibrary.find("GameLogo") == textureLibrary.end())
		{
			textureLibrary.insert({ "GameLogo", AEGfxTextureLoad("res/GameLogo.png") });
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
		if (textureLibrary.find("Exit_1") == textureLibrary.end())
		{
			textureLibrary.insert({ "Exit_1", AEGfxTextureLoad("res/Exit_1.png") });
		}
		if (textureLibrary.find("Exit_2") == textureLibrary.end())
		{
			textureLibrary.insert({ "Exit_2", AEGfxTextureLoad("res/Exit_2.png") });
		}
		if (textureLibrary.find("Exit_3") == textureLibrary.end())
		{
			textureLibrary.insert({ "Exit_3", AEGfxTextureLoad("res/Exit_3.png") });
		}
		if (textureLibrary.find("Bullet_1") == textureLibrary.end())
		{
			textureLibrary.insert({ "Bullet_1", AEGfxTextureLoad("res/Weapon_Bullet1.png") });
		}
		if (textureLibrary.find("Checkbox") == textureLibrary.end())
		{
			textureLibrary.insert({ "Checkbox", AEGfxTextureLoad("res/Checkbox.png") });
		}
		if (textureLibrary.find("Tutorial_planet") == textureLibrary.end())
		{
			textureLibrary.insert({ "Tutorial_planet", AEGfxTextureLoad("res/Tutorial_planet.png") });
		}
		if (textureLibrary.find("Credits_1") == textureLibrary.end())
		{
			textureLibrary.insert({ "Credits_1", AEGfxTextureLoad("res/Credits_1.png") });
		}
		if (textureLibrary.find("Credits_2") == textureLibrary.end())
		{
			textureLibrary.insert({ "Credits_2", AEGfxTextureLoad("res/Credits_2.png") });
		}
		if (textureLibrary.find("Credits_3") == textureLibrary.end())
		{
			textureLibrary.insert({ "Credits_3", AEGfxTextureLoad("res/Credits_3.png") });
		}
		if (textureLibrary.find("Credits_4") == textureLibrary.end())
		{
			textureLibrary.insert({ "Credits_4", AEGfxTextureLoad("res/Credits_4.png") });
		}
		if (textureLibrary.find("Credits_5") == textureLibrary.end())
		{
			textureLibrary.insert({ "Credits_5", AEGfxTextureLoad("res/Credits_5.png") });
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
					if (textureLibrary.find("Bullet_2") != textureLibrary.end()) break;
					textureLibrary.insert({"Bullet_2", AEGfxTextureLoad("res/Weapon_Bullet2.png") });
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
					break;
				case 16:
					if (textureLibrary.find("Low_Health") != textureLibrary.end()) break;
					textureLibrary.insert({ "Low_Health", AEGfxTextureLoad("res/Low_Health.png") });
					break;
				case 17: 
					if (textureLibrary.find("Asteroid_1") != textureLibrary.end()) break;
					textureLibrary.insert({ "Asteroid_1", AEGfxTextureLoad("res/Asteroid_1.png") });
					break;
				case 18: 
					if (textureLibrary.find("Asteroid_2") != textureLibrary.end()) break;
					textureLibrary.insert({ "Asteroid_2", AEGfxTextureLoad("res/Asteroid_2.png") });
					break;
				case 19: 
					if (textureLibrary.find("Boss_Incoming") != textureLibrary.end()) break;
					textureLibrary.insert({ "Boss_Incoming", AEGfxTextureLoad("res/Boss_Incoming.png") });
					break;
				case 20: 
					if (textureLibrary.find("Shield_Down") != textureLibrary.end()) break;
					textureLibrary.insert({ "Shield_Down", AEGfxTextureLoad("res/Shield_Down.png") });
					break;
				case 21:
					if (textureLibrary.find("Boss") != textureLibrary.end()) break; 
					textureLibrary.insert({ "Boss", AEGfxTextureLoad("res/Boss.png") });
					break;
				case 22:
					if (textureLibrary.find("Upgrade_Health") != textureLibrary.end()) break;
					textureLibrary.insert({ "Upgrade_Health", AEGfxTextureLoad("res/Upgrade_Health.png") });
					break;
				case 23:
					if (textureLibrary.find("Upgrade_Damage") != textureLibrary.end()) break;
					textureLibrary.insert({ "Upgrade_Damage", AEGfxTextureLoad("res/Upgrade_Damage.png") });
					break;
				case 24:
					if (textureLibrary.find("Upgrade_Shield") != textureLibrary.end()) break;
					textureLibrary.insert({ "Upgrade_Shield", AEGfxTextureLoad("res/Upgrade_Shield.png") });
					break;
				case 25:
					if (textureLibrary.find("Upgrade_Thruster") != textureLibrary.end()) break;
					textureLibrary.insert({ "Upgrade_Thruster", AEGfxTextureLoad("res/Upgrade_Thruster.png") });
					break;
				case 26:
					if (textureLibrary.find("Upgrade_Laser") != textureLibrary.end()) break;
					textureLibrary.insert({ "Upgrade_Laser", AEGfxTextureLoad("res/Upgrade_Laser.png") });
					break;
				case 27:
					if (textureLibrary.find("Enemy_1_5") != textureLibrary.end()) break;
					textureLibrary.insert({ "Enemy_1_5", AEGfxTextureLoad("res/Enemy_1_5.png") });
					break;
				case 28:
					if (textureLibrary.find("Objective_Symbol") != textureLibrary.end()) break;
					textureLibrary.insert({ "Objective_Symbol", AEGfxTextureLoad("res/Objective_Symbol.png") });
					break;
				case 29:
					if (textureLibrary.find("Skull_Normal") != textureLibrary.end()) break;
					textureLibrary.insert({ "Skull_Normal", AEGfxTextureLoad("res/Skull_Normal.png") });
					break;
				case 30:
					if (textureLibrary.find("Skull_Boss") != textureLibrary.end()) break;
					textureLibrary.insert({ "Skull_Boss", AEGfxTextureLoad("res/Skull_Boss.png") });
					break;
				case 31:
					if (textureLibrary.find("Scanner") != textureLibrary.end()) break;
					textureLibrary.insert({ "Scanner", AEGfxTextureLoad("res/Player_Shield.png") });
					break;
				case 32:
					if (textureLibrary.find("Pause_Menu") != textureLibrary.end()) break;
					textureLibrary.insert({ "Pause_Menu", AEGfxTextureLoad("res/Pause_Menu.png") });
					break;
				case 33:
					if (textureLibrary.find("Pause_Confirmation") != textureLibrary.end()) break;
					textureLibrary.insert({ "Pause_Confirmation", AEGfxTextureLoad("res/Pause_confirmation.png") });
					break;
				case 34:
					if (textureLibrary.find("UI_Mission1") != textureLibrary.end()) break;
					textureLibrary.insert({ "UI_Mission1", AEGfxTextureLoad("res/UI_Mission1.png") });
					break;
				case 35:
					if (textureLibrary.find("UI_Mission2") != textureLibrary.end()) break;
					textureLibrary.insert({ "UI_Mission2", AEGfxTextureLoad("res/UI_Mission2.png") });
					break;
				case 36:
					if (textureLibrary.find("UI_Mission3") != textureLibrary.end()) break;
					textureLibrary.insert({ "UI_Mission3", AEGfxTextureLoad("res/UI_Mission3.png") });
					break;
				case 37:
					if (textureLibrary.find("Settings_Icon") != textureLibrary.end()) break;
					textureLibrary.insert({ "Settings_Icon", AEGfxTextureLoad("res/Settings_Icon.png") });
					break;
				case 38:
					if (textureLibrary.find("GameOver_Menu") != textureLibrary.end()) break;
					textureLibrary.insert({ "GameOver_Menu", AEGfxTextureLoad("res/GameOver_Menu.png") });
					break;
				case 39: 
					if (textureLibrary.find("GameWin_Menu") != textureLibrary.end()) break;
					textureLibrary.insert({ "GameWin_Menu", AEGfxTextureLoad("res/GameWin_Menu.png") });
					*progress = 100;
					break;
				
			}
			*progress < 100? *progress += static_cast<unsigned int>(100 / 40): *progress = 100;
			Console_Cout("Loading process", static_cast<int>(*progress));
			++*stage;
			AEGetTime(&currTime);
		}
	}

	void LoadTextureLibrary_2(unsigned int* stage, unsigned int* progress)
	{
		f64 currTime, startTime;
		AEGetTime(&currTime);
		AEGetTime(&startTime);

		while (currTime - startTime < 1.0f / 60.0f && *progress < 100)
		{
			switch (*stage)
			{
			case 0:
				if (textureLibrary.find("Delivery") != textureLibrary.end()) break;
				textureLibrary.insert({ "Delivery", AEGfxTextureLoad("res/Delivery.png") });
				*progress = 100;
				break;
			}
			*progress < 100 ? *progress += static_cast<unsigned int>(100 / 1) : *progress = 100;
			++* stage;
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
/**********************************************************************************
* \file			Level1.cpp
* \brief		Game State for Level 1
* \author		Wei Feng,		Ang,		25% Code Contribution
*				Jun Yi,			Chong,		25% Code Contribution
*				Jin Kiat,		Chong,		25% Code Contribution
*               Farzaana Binte, Roslan,     25%  Code Contribution
* 
*				Long Description
*				- Initalise game objects into the level
*				- Update - Render Loop
*				- Memory Cleanup
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Level1.h"									//Self Header
#include "../ECS/Core.h"							//Systems to Update
#include "../ECS/Factory.h"							//Entity to create
#include "../Player/PlayerManager.h"				//Control over the player
#include "../Managers/UIEventsManager.h"
#include "../Managers/AudioManager.h"
#include "../Managers/LevelManager.h"
#include "../Systems/UISystem.h"
#include "../Systems/RenderSystem.h"


#include "../Tools/Console.h"
#include "../Tools/Editor.h"
ENTITY enemy;
ENTITY objectiveUI;
ENTITY toggleObjectiveTickbox_state;
const float bossSpawn = 1.0f;
float bossSpawnTimer = 0.0f;
bool spawnedBoss = false;
ENTITY referencetoLevelDisplay = 0;
int count = 0;									//Animation Step
float currTimer = 0.0f;
// ----------------------------------------------------------------------------
// This function loads all necessary assets in Level1
// It should be called once before the start of the level
// It loads assets like textures, meshes and music files etc…
// ----------------------------------------------------------------------------
void Level1_Load()
{
	// Create Level name 
	referencetoLevelDisplay = Factory_UI::CreateUI_Level1Display();

	//Create Player
	PlayerManager::player = Factory::CreatePlayer(2);

	//Create a debug arrow on player
	Factory::DebugVector_Velocity(PlayerManager::player);

	// Create camera
	Factory::CreateCamera(PlayerManager::player);

	LevelManager::Level1_Setup();

	// Planet to test for collision
	Factory::CreatePlanet2(4, 100.0f, 150.0f, 100.0f, 100.0f);
	Factory::CreatePlanet2(3, 200.0f, 179.0f, 200.0f, 200.0f);
	Factory::CreatePlanet4(3, 700.0f, -300.0f, 700.0f, 700.0f);
	Factory::CreatePlanet2(5, -30.0f, -200.0f, 30.0f, 30.0f);

	Factory::CreatePlanet3(4, 400.0f, 400.0f, 230.0f, 230.0f);
	Factory::CreatePlanet3(4, 630.0f, -40.0f, 60.0f, 60.0f);
	Factory::CreatePlanet3(4, -300.0f, -400.0f, 400.0f, 400.0f);
	Factory::CreatePlanet3(4, 1000.0f, 240.0f, 100.0f, 100.0f);

	Factory::CreatePlanet1(3, -400.0f, 200.0f, 100.0f, 100.0f);
	Factory::CreatePlanet4(5, 730.0f, 30.0f, 80.0f, 80.0f);
	Factory::CreatePlanet1(5, -820.0f, -100.0f, 200.0f, 200.0f);
	Factory::CreatePlanet1(5, 1300.0f, -90.0f, 100.0f, 100.0f);

	// Creating of asteroids
	Factory::CreateAsteroid1(2, 50.0f, -200.f, 100.0f, 100.0f);
	Factory::CreateAsteroid1(2, 600.0f, 250.f, 80.0f, 80.0f);
	Factory::CreateAsteroid1(2, -800.0f, -200.f, 80.0f, 80.0f);
	Factory::CreateAsteroid1(2, 200.0f, -200.f, 150.0f, 150.0f);

	Factory::CreateAsteroid2(2, 350.0f, -300.0f, 80.0f, 80.0f);
	Factory::CreateAsteroid2(2, 270.0f, 180.0f, 120.0f, 120.0f);
	Factory::CreateAsteroid2(2, -900.0f, 300.0f, 80.0f, 80.0f);
	Factory::CreateAsteroid2(2, 80.0f, -260.0f, 60.0f, 60.0f);

	Factory_Map::Generate_PlanetField();

	Factory::CreateBackground();
	objectiveUI = Factory_UI::CreateUI_AddObjective(1, "Save 3 Stranded Allies");
	toggleObjectiveTickbox_state = Core::Get().GetComponent<cUIElement>(objectiveUI)->_roleIndex;
	Factory_UI::Create_PlayerUserInterface(3, 3);
	Factory_UI::CreateUI_Pause();				//Create a Pause UI but make it invisible

	// FOR NOW, audio
	AudioManager::LoadSound("res/BGM/cinescifi.wav", true);
}

// ----------------------------------------------------------------------------
// This function initalise all necessary data in Level1
// It should be called once before the start of the level
// It resets data like counters to inital values�
// ----------------------------------------------------------------------------
void Level1_Init()
{
	AudioManager::PlayBGM("res/BGM/cinescifi.wav", 0.25f);
}

// ----------------------------------------------------------------------------
// This function updates the data within Level1
// Update functions such as user input, time or gameplay logic
// ----------------------------------------------------------------------------
void Level1_Update()
{
	if (currTimer <= 4.0f)
	{
		currTimer += g_dt;
		if (currTimer >= 2.0f)
		{
			RenderingTricks::LightSpeedEffectOut(referencetoLevelDisplay, currTimer - 2.0f, count++, 5.0f, 0.04f, -60.0f);
			if (currTimer > 4.0f)
			{
				Core::Get().EntityDestroyed(referencetoLevelDisplay);
			}
		}

	}

	if (PlayerManager::player)
	{
		AEVec2 playerPos = Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position;
		//Spawn Enemy around player
		LevelManager::EnemySpawnManager::SpawnEnemyWavesTimer(playerPos, 5.0f);
	}

	if (LevelManager::objectiveComplete)
	{
		Core::Get().GetComponent<cSprite>(toggleObjectiveTickbox_state)->_colorTint.a = 1.0f;
	}
	//Editor_TrackVariable("ACTIVE ENTITY COUNT", static_cast<int>(Core::Get().GetEntityCount()));
	Console_Cout("ACTIVE ENTITY COUNT", static_cast<int>(Core::Get().GetEntityCount()));
	AudioManager::Update();
	PlayerManager::Update();
	LevelManager::Level1_Update();
	Core::Get().Core_Update();
	


	if (AEInputCheckTriggered(AEVK_L))
	{
		Factory_UI::CreateUI_AddObjective_Finale(2, "Eliminate The Boss!");
	}
}

// ----------------------------------------------------------------------------
// This function renders the graphics for each frame of Level1
// Sends data to the graphics engine component
// ----------------------------------------------------------------------------
void Level1_Draw()
{
	Core::Get().Core_Render();
}
// ----------------------------------------------------------------------------
// This function cleans up the game state for Level1
// Make the state ready to be unloaded or initialized again
// No data is dumped in this cycle function
// ----------------------------------------------------------------------------
void Level1_Free()
{
	currTimer = 0.0f;
	count = 0;
	AudioManager::UnLoadAllSounds();
	LevelManager::ClearObjectiveAll();
}
// ----------------------------------------------------------------------------
// This function dumps all data loaded in Level 1
// Is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{
	CleanUpIndicator();
	UIEventsManager::Cleanup();
	Factory::RemoveCamera();
	Core::Get().DestroyAllEntity();
}


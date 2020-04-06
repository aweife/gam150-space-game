/**********************************************************************************
* \file			Level2.cpp
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
#include "Level2.h"									//Self Header
#include "../ECS/Core.h"							//Systems to Update
#include "../ECS/Factory.h"							//Entity to create
#include "../Player/PlayerManager.h"				//Control over the player
#include "../Managers/UIEventsManager.h"
#include "../Managers/AudioManager.h"
#include "../Managers/LevelManager.h"
#include "../Systems/RenderSystem.h"

#include "../Tools/Console.h"
#include "../Tools/Editor.h"

ENTITY reftoLevelDisplay = 0;
int _count = 0;									//Animation Step
float _currTimer = 0.0f;
ENTITY package = 0;
ENTITY deliveryPackageUI;
ENTITY enemyDestroyedUI;
ENTITY enemyDestroyedUITickbox_state;
ENTITY deliveryPackageUIickbox_state;
// ----------------------------------------------------------------------------
// This function loads all necessary assets in Level1
// It should be called once before the start of the level
// It loads assets like textures, meshes and music files etc…
// ----------------------------------------------------------------------------
void Level2_Load()
{
	// Create Level name 
	reftoLevelDisplay = Factory_UI::CreateUI_Level2Display();

	//Create Player
	PlayerManager::player = Factory::CreatePlayer(2);

	//Create a debug arrow on player
	Factory::DebugVector_Velocity(PlayerManager::player);

	// Create camera
	Factory::CreateCamera(PlayerManager::player);

	LevelManager::Level2_Setup();

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

	package = Factory::SpawnDelivery({0.0f, 200.0f}, 60.0f, 5.0f, { 50.0f,50.0f });


	Factory::CreateBackground();
	deliveryPackageUI = Factory_UI::CreateUI_AddObjective(1, "Deliver The Package");
	deliveryPackageUIickbox_state = Core::Get().GetComponent<cUIElement>(deliveryPackageUI)->_roleIndex;

	enemyDestroyedUI = Factory_UI::CreateUI_AddObjective(2, "Eliminate 10 enemies");
	enemyDestroyedUITickbox_state = Core::Get().GetComponent<cUIElement>(enemyDestroyedUI)->_roleIndex;
	
	Factory_UI::Create_PlayerUserInterface();
	Factory_UI::CreateUI_Pause();				//Create a Pause UI but make it invisible

	// FOR NOW, audio
	AudioManager::LoadSound("res/BGM/cinescifi.wav", true);
}

// ----------------------------------------------------------------------------
// This function initalise all necessary data in Level1
// It should be called once before the start of the level
// It resets data like counters to inital values…
// ----------------------------------------------------------------------------
void Level2_Init()
{
	//spawnedBoss = false;
	AudioManager::PlayBGM("res/BGM/cinescifi.wav", 0.25f);
}

// ----------------------------------------------------------------------------
// This function updates the data within Level1
// Update functions such as user input, time or gameplay logic
// ----------------------------------------------------------------------------
void Level2_Update()
{
	if (_currTimer <= 4.0f)
	{
		_currTimer += g_dt;
		if (_currTimer >= 2.0f)
		{
			RenderingTricks::LightSpeedEffectOut(reftoLevelDisplay, _currTimer - 2.0f, _count++, 5.0f, 0.04f, -60.0f);
			if (_currTimer > 4.0f)
			{
				Core::Get().EntityDestroyed(reftoLevelDisplay);
			}
		}

	}
	AudioManager::Update();
	PlayerManager::Update();
	if (PlayerManager::player)
	{
		AEVec2 playerPos = Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position;
		//Delivery Mission
		LevelManager::Level2Update(playerPos, 5.0f);
		//Spawn Enemy around player
		LevelManager::EnemySpawnManager::SpawnEnemyWavesTimer(playerPos, 5.0f);
	}

	if (LevelManager::enemyObjectiveComplete)
	{
		Core::Get().GetComponent<cSprite>(enemyDestroyedUITickbox_state)->_colorTint.a = 1.0f;
	}

	if (LevelManager::isCollectedCompleted)
	{
		Core::Get().GetComponent<cSprite>(deliveryPackageUIickbox_state)->_colorTint.a = 1.0f;

	}


	Core::Get().Core_Update();

	
	
}

// ----------------------------------------------------------------------------
// This function renders the graphics for each frame of Level1
// Sends data to the graphics engine component
// ----------------------------------------------------------------------------
void Level2_Draw()
{
	Core::Get().Core_Render();
}
// ----------------------------------------------------------------------------
// This function cleans up the game state for Level1
// Make the state ready to be unloaded or initialized again
// No data is dumped in this cycle function
// ----------------------------------------------------------------------------
void Level2_Free()
{
	_currTimer = 0.0f;
	_count = 0;
	//spawnedBoss = false;
	AudioManager::UnLoadAllSounds();
	LevelManager::ClearObjectiveAll();
}
// ----------------------------------------------------------------------------
// This function dumps all data loaded in Level 1
// Is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level2_Unload()
{
	UIEventsManager::Cleanup();
	Factory::RemoveCamera();
	Core::Get().DestroyAllEntity();
}


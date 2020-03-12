/*********************************************************************************
* \file			Editor.cpp
* \author		Chong Jun Yi, Ang Wei Feng, Chong Jin Kiat, Farzaana Binte Roslan
* \version		1.0
* \date			25/01/2020
* \par			Level Game State
* \note			Course: GAM150
* \brief		Level 1 Game State
				-
				-

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Level1.h"									//Self Header
#include "../ECS/Core.h"							//Systems to Update
#include "../ECS/Factory.h"							//Entity to create
#include "../Player/PlayerManager.h"				//Control over the player
#include "../Managers/UIEventsManager.h"
#include "../Managers/AudioManager.h"

#include "../Tools/Console.h"
#include "../Tools/Editor.h"
ENTITY enemy;
// ----------------------------------------------------------------------------
// This function loads all necessary assets in Level1
// It should be called once before the start of the level
// It loads assets like textures, meshes and music files etc…
// ----------------------------------------------------------------------------
void Level1_Load()
{
	//Create Player
	PlayerManager::player = Factory::CreatePlayer(2);

	//Create a debug arrow on player
	Factory::DebugVector_Velocity(PlayerManager::player);

	// Create camera
	Factory::CreateCamera(PlayerManager::player);		

	//Create Enemy
	enemy = Factory::CreateEnemy1(PlayerManager::player, 2);
	enemy = Factory::CreateEnemy2(PlayerManager::player, 2);

	// Planet to test for collision
	Factory::CreatePlanet2(4, 100.0f, 150.0f, 100.0f, 100.0f);
	Factory::CreatePlanet2(3, 200.0f, 179.0f, 200.0f, 200.0f);
	Factory::CreatePlanet4(3, 700.0f, -300.0f, 700.0f, 700.0f);
	Factory::CreatePlanet2(5, -30.0f, -200.0f, 30.0f, 30.0f);

	Factory::CreatePlanet3(4, 400.0f, 400.0f, 230.0f, 230.0f);
	Factory::CreatePlanet3(4, 630.0f, -40.0f, 60.0f, 60.0f);
	Factory::CreatePlanet3(4, -300.0f, -400.0f, 400.0f, 400.0f);
	Factory::CreatePlanet3(4, 1000.0f, 240.0f, 100.0f, 100.0f);

	Factory::CreatePlanet1(3, -400.0f, 200.0f, 100.0f, 100.0f );
	Factory::CreatePlanet4(5, 730.0f, 30.0f, 80.0f, 80.0f);
	Factory::CreatePlanet1(5, -820.0f, -100.0f, 200.0f, 200.0f);
	Factory::CreatePlanet1(5, 1300.0f, -90.0f, 100.0f, 100.0f);

	Factory::CreateBackground();
	Factory_UI::Create_PlayerUserInterface();

	// FOR NOW, audio
	AudioManager::LoadSound("res/BGM/cinescifi.wav", true);
}

// ----------------------------------------------------------------------------
// This function initalise all necessary data in Level1
// It should be called once before the start of the level
// It resets data like counters to inital values…
// ----------------------------------------------------------------------------
void Level1_Init()
{
	AudioManager::PlayOneShot("res/BGM/cinescifi.wav", 0.25f);
}

// ----------------------------------------------------------------------------
// This function updates the data within Level1
// Update functions such as user input, time or gameplay logic
// ----------------------------------------------------------------------------
void Level1_Update()
{
	AudioManager::Update();
	PlayerManager::Update();
	Core::Get().Core_Update();
	if (AEInputCheckTriggered(AEVK_1))
	{
		Core::Get().EntityDestroyed(enemy);
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
	AudioManager::UnLoadAllSounds();
}
// ----------------------------------------------------------------------------
// This function dumps all data loaded in Level 1
// Is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}


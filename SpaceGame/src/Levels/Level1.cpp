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
#include "Level1.h"
#include "../Tools/Console.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"

ENTITY player;
ENTITY planet;

// ----------------------------------------------------------------------------
// This function loads all necessary assets in Level1
// It should be called once before the start of the level
// It loads assets like textures, meshes and music files etc…
// ----------------------------------------------------------------------------
void Level1_Load()
{
	player = Core::Get().CreateEntity();
	Core::Get().AddComponent<cTransform>(player, new cTransform);
	Core::Get().AddComponent<cSprite>(player, new cSprite(player, "res/machinegun.png"));
	Core::Get().AddComponent<cRigidBody>(player, new cRigidBody);
	Core::Get().AddComponent<cCollision>(player, new cCollision);
	Core::Get().AddComponent<cPathFinding>(player, new cPathFinding);
	Core::Get().AddComponent<cAI>(player, new cAI);

	// Planet to test for collision
	planet = Core::Get().CreateEntity();
	Core::Get().AddComponent<cTransform>(planet, new cTransform);
	Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "res/Planet2.png"));
	Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody);
	Core::Get().AddComponent<cCollision>(planet, new cCollision);
	Core::Get().AddComponent<cPathFinding>(planet, new cPathFinding);
}

// ----------------------------------------------------------------------------
// This function initalise all necessary data in Level1
// It should be called once before the start of the level
// It resets data like counters to inital values…
// ----------------------------------------------------------------------------
void Level1_Init()
{
	// Player
	Core::Get().GetComponent<cTransform>(player)->scale.x = 50.0f;
	Core::Get().GetComponent<cTransform>(player)->scale.y = 50.0f;
	Core::Get().GetComponent<cTransform>(player)->position.x = -200.0f;
	Core::Get().GetComponent<cTransform>(player)->position.y = 0.0f;
	Core::Get().GetComponent<cRigidBody>(player)->velocity = 150.0f;
	Core::Get().GetComponent<cRigidBody>(player)->velocityVector.x = 1.0f;
	Core::Get().GetComponent<cRigidBody>(player)->velocityVector.y = -1.0f;
	Core::Get().GetComponent<cPathFinding>(player)->target = planet;
	Core::Get().GetComponent<cPathFinding>(player)->currentState = PATH_SEEK;
	Core::Get().GetComponent<cAI>(player)->minDistance = 300.0f;
	Core::Get().GetComponent<cAI>(player)->maxDistance = 500.0f;

	// Planet
	Core::Get().GetComponent<cTransform>(planet)->position.x = 0.0f;
	Core::Get().GetComponent<cTransform>(planet)->position.y = -200.0f;
	Core::Get().GetComponent<cRigidBody>(planet)->velocity = 100.0f;
	Core::Get().GetComponent<cRigidBody>(planet)->velocityVector.x = -0.5f;
	Core::Get().GetComponent<cRigidBody>(planet)->velocityVector.y = 0.5f;
}

// ----------------------------------------------------------------------------
// This function updates the data within Level1
// Update functions such as user input, time or gameplay logic
// ----------------------------------------------------------------------------
void Level1_Update()
{
	Core::Get().Core_Update();
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

}
// ----------------------------------------------------------------------------
// This function dumps all data loaded in Level 1
// Is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{

}
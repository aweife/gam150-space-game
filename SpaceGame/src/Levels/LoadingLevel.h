/**********************************************************************************
* \file			LoadingLevel.h
* \brief		Game State for Loading Level
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Provide a loading screen
*				- While loading assets within the delta time of each frame
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

extern unsigned int loadingForState;

// ----------------------------------------------------------------------------
// This function loads all necessary assets in Level1
// It should be called once before the start of the level
// It loads assets like textures, meshes and music files etc…
// ----------------------------------------------------------------------------
void LoadingLvl_Load();

// ----------------------------------------------------------------------------
// This function initalise all necessary data in Level1
// It should be called once before the start of the level
// It resets data like counters to inital values…
// ----------------------------------------------------------------------------
void LoadingLvl_Init();

// ----------------------------------------------------------------------------
// This function updates the data within Level1
// Update functions such as user input, time or gameplay logic
// ----------------------------------------------------------------------------
void LoadingLvl_Update();

// ----------------------------------------------------------------------------
// This function renders the graphics for each frame of Level1
// Sends data to the graphics engine component
// ----------------------------------------------------------------------------
void LoadingLvl_Draw();

// ----------------------------------------------------------------------------
// This function cleans up the game state for Level1
// Make the state ready to be unloaded or initialized again
// No data is dumped in this cycle function
// ----------------------------------------------------------------------------
void LoadingLvl_Free();

// ----------------------------------------------------------------------------
// This function dumps all data loaded in Level 1
// Is called when the state should be terminated
// ----------------------------------------------------------------------------
void LoadingLvl_Unload();

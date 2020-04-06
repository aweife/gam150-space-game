/**********************************************************************************
* \file			Level1.h
* \brief		Game State for Level 1
* \author		Wei Feng,		Ang,		25% Code Contribution
*				Jun Yi,			Chong,		25% Code Contribution
*				Jin Kiat,		Chong,		25% Code Contribution
*               Farzaana Binte, Roslan,     25% Code Contribution
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
#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H

// ----------------------------------------------------------------------------
// This function loads all necessary assets in Level1
// It should be called once before the start of the level
// It loads assets like textures, meshes and music files etc…
// ----------------------------------------------------------------------------
void Level1_Load();

// ----------------------------------------------------------------------------
// This function initalise all necessary data in Level1
// It should be called once before the start of the level
// It resets data like counters to inital values…
// ----------------------------------------------------------------------------
void Level1_Init();

// ----------------------------------------------------------------------------
// This function updates the data within Level1
// Update functions such as user input, time or gameplay logic
// ----------------------------------------------------------------------------
void Level1_Update();

// ----------------------------------------------------------------------------
// This function renders the graphics for each frame of Level1
// Sends data to the graphics engine component
// ----------------------------------------------------------------------------
void Level1_Draw();

// ----------------------------------------------------------------------------
// This function cleans up the game state for Level1
// Make the state ready to be unloaded or initialized again
// No data is dumped in this cycle function
// ----------------------------------------------------------------------------
void Level1_Free();

// ----------------------------------------------------------------------------
// This function dumps all data loaded in Level 1
// Is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload();

#endif

/**********************************************************************************
* \file			MainMenu.h
* \brief		Game State for Main Menu
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Play, Options, Credits, Exit
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

enum class mmStates { MAIN, OPTIONS, CREDITS };

void MainMenu_Load();
void MainMenu_Init();
void MainMenu_Update();
void MainMenu_Draw();
void MainMenu_Free();
void MainMenu_Unload();

void Create_MainMenuInterface();
void Switch_MainMenuState(mmStates newState);


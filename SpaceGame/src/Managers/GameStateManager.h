/**********************************************************************************
* \file			GameStateManager.h
* \brief		Manage Gamestates change during the game
* \author		Chong Jun Yi, 25% Code Contribution
* \author		Chong Jin Kiat, 25% Code Contribution
* \author		Ang Wei Feng, 25% Code Contribution
* \author		Farzaana Binte Roslan, 25% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once

enum GAMESTATE
{
	GS_LOADINGSCREEN,

	GS_SPLASHSCREEN,
	GS_MAINMENU,
	GS_LEVEL1,
	GS_LEVEL2,
	GS_LEVEL3,
	GS_UPGRADE,

	GS_QUIT,
	GS_RESTART,
	GS_NULL
};

	//The sequence of game states
extern unsigned int currentState;
extern unsigned int previousState;
extern unsigned int nextState;

//The 6 function pointer for the essential stages of game loop
extern void (*fpLoad)();
extern void (*fpInit)();
extern void (*fpUpdate)();
extern void (*fpDraw)();
extern void (*fpFree)();
extern void (*fpUnload)(); 

void GSM_Init(int startGameState);
void GSM_Update();
void GSM_RestartLevel();
void GSM_QuitGame();
void GSM_ChangeState(int nextGameState);
void GSM_LoadingTransition(int loadForState);
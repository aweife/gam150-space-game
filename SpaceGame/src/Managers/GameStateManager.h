#pragma once

enum GAMESTATE
{
	GS_LOADINGLvl,
	GS_SPLASHSCREEN,
	GS_MAINMENU,
	GS_LEVEL1,

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
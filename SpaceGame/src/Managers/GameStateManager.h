#pragma once

enum GAMESTATE
{
	GS_LEVEL1,

	GS_QUIT,
	GS_RESTART
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

#include "GameStateManager.h"
#include "../Levels/LoadingLevel.h"
#include "../Levels/Level1.h"

#include "../Tools/Console.h"
unsigned int currentState, previousState, nextState;

void (*fpLoad)();
void (*fpInit)();
void (*fpUpdate)();
void (*fpDraw)();
void (*fpFree)();
void (*fpUnload)();

void GSM_Init(int startGameState)
{
	currentState = previousState = nextState = startGameState;
	fpLoad = fpInit = fpUpdate = fpDraw = fpFree = fpUnload = nullptr;
}

void GSM_Update()
{
	switch (nextState)
	{
	case GS_LOADINGLvl:
		fpLoad =	LoadingLvl_Load;
		fpInit =	LoadingLvl_Init;
		fpUpdate =	LoadingLvl_Update;
		fpDraw =	LoadingLvl_Draw;
		fpFree =	LoadingLvl_Free;
		fpUnload =	LoadingLvl_Unload;
		break;
	case GS_LEVEL1:
		fpLoad =	Level1_Load;
		fpInit =	Level1_Init;
		fpUpdate =	Level1_Update;
		fpDraw =	Level1_Draw;
		fpFree =	Level1_Free;
		fpUnload =	Level1_Unload;
		break;
	case GS_RESTART:
		break;
	case GS_QUIT:
		break;
	default:
		break;
	}
}

void GSM_RestartLevel()
{
	Console_Cout("Restart Level");
	nextState = GS_RESTART;
}

void GSM_QuitGame()
{
	Console_Cout("Quite Game");
	nextState = GS_QUIT;
}

void GSM_ChangeState(int nextGameState)
{
	Console_Cout("Change State ");
	nextState = nextGameState;
}

void GSM_LoadingTransition(int loadForState)
{
	Console_Cout("Loading Level Assets");
	loadingForState = loadForState;
	nextState = GS_LOADINGLvl;
}
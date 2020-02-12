#include "GameStateManager.h"
#include "../Levels/Level1.h"

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
	case GS_LEVEL1:
		fpLoad = Level1_Load;
		fpInit = Level1_Init;
		fpUpdate = Level1_Update;
		fpDraw = Level1_Draw;
		fpFree = Level1_Free;
		fpUnload = Level1_Unload;
		break;
	case GS_RESTART:
		break;
	case GS_QUIT:
		break;
	default:
		break;
	}
}
/**********************************************************************************
* \file			SplashScreen.cpp
* \brief		Game State for Splash Screen
* \author		Farzaana Binte,Roslan,		100% Code Contribution
*
*				Long Description
*				- Loading the missions name of each level
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "LevelDisplay.h"
#include "../ECS/Factory.h"
#include "../Managers/AudioManager.h"
#include "../Managers/UIEventsManager.h"
#include "../Managers/GameStateManager.h"

#include "../Systems/RenderSystem.h"		//RenderingTricks

const float displayTime[2] = { 2.0f, 1.0f };
const float preanimationTime[2] = { 0.0f, 1.0f };
const float postanimationTime[2] = { 0.0f, 1.0f };
float currTimer = 0.0f;							    //Timer
unsigned int levelDisplayStage = 0;					//Which image to show
int aniCounter = 0;									//Animation Step

ENTITY currentLevelDisplay = 0;
enum class levelDisplayState { level1, level2, level3 };
levelDisplayState currState = levelDisplayState::level1;

unsigned int loadState = GS_NULL;
ENTITY loadText = 0;

void LevelDisplay_Load()
{
	loadText = Factory_UI::CreateUI_Text(0, 0, "PILGRIM");
	currentLevelDisplay = Factory_LevelDisplay::CreateLevelDisplay_Level1();
}
void LevelDisplay_Init()
{
	AEGfxSetBackgroundColor(0.00f, 0.00f, 0.90f);
	currTimer = 0.0f;
	levelDisplayStage = 0;
}

void LevelDisplay_Update()
{
	currTimer += g_dt;
	switch (currState)
	{
	case levelDisplayState::level1:
		RenderingTricks::LightSpeedEffectIn(currentLevelDisplay, currTimer, postanimationTime[levelDisplayStage], 0.5f
			, aniCounter++, 100.0f, 100.0f, 0.0f, 0.0f, 0.02f, 60.0f);
		if (currTimer > preanimationTime[levelDisplayStage])
		{
			aniCounter = 0;
			currTimer = 0.0f;
			LevelDisplayIntervals();
		}
		break;
	case levelDisplayState::level2:
		if (currTimer > displayTime[levelDisplayStage])
		{
			currTimer = 0.0f;
			currState = levelDisplayState::level3;
		}
		break;
	case levelDisplayState::level3:
		/*RenderingTricks::LightSpeedEffectOut(currentLevelDisplay, currTimer, aniCounter++, 10.0f, 0.04f, -60.0f);
		if (currTimer > postanimationTime[levelDisplayStage])
		{
			aniCounter = 0;
			currTimer = 0.0f;
			++levelDisplayStage;
			currState = levelDisplayState::level1;
			LevelDisplayIntervals();
		}*/
		break;
	}
}
void LevelDisplay_Draw()
{
	Core::Get().Core_Render();
}
void LevelDisplay_Free()
{
	AEGfxSetBackgroundColor(0.07f, 0.04f, 0.22f);
	AudioManager::UnLoadAllSounds();
}
void LevelDisplay_Unload()
{
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}

void LevelDisplayIntervals()
{
	switch (levelDisplayStage)
	{
	case 1:
		Core::Get().EntityDestroyed(currentLevelDisplay);
		currentLevelDisplay = Factory_LevelDisplay::CreateLevelDisplay_Level1();
		GSM_ChangeState(GS_LEVEL1);
		break;
	case 2: 
		Core::Get().EntityDestroyed(currentLevelDisplay);
		currentLevelDisplay = Factory_LevelDisplay::CreateLevelDisplay_Level2();
		break; 
	case 3: 
		Core::Get().EntityDestroyed(currentLevelDisplay);
		currentLevelDisplay = Factory_LevelDisplay::CreateLevelDisplay_Level3();
		break;
	default:
		AEGfxSetBackgroundColor(0.07f, 0.04f, 0.22f);								// Set Dark Purple BG 
		GSM_ChangeState(GS_NULL);
		break;
	}
}
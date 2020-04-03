/**********************************************************************************
* \file			SplashScreen.cpp
* \brief		Game State for Splash Screen
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Digipen and moonbase logo
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "SplashScreen.h"
#include "../ECS/Factory.h"
#include "../Managers/AudioManager.h"
#include "../Managers/UIEventsManager.h"
#include "../Managers/GameStateManager.h"

#include "../Systems/RenderSystem.h"		//RenderingTricks

const float displayTime[2] = { 0.0f, 0.0f };//{ 2.0f, 1.0f };
const float preanimationTime[2] = { 0.0f, 0.0f };//{ 0.0f, 1.0f };
const float postanimationTime[2] = { 0.0f, 0.0f };//{ 0.0f, 1.0f };
float currentTimer = 0.0f;							//Timer
unsigned int splashScreenStage = 0;					//Which image to show
int counter = 0;									//Animation Step

ENTITY currentSplashScreen = 0;
enum class splashScreenState {preAnim, display, postAnim};
splashScreenState currState = splashScreenState::preAnim;

void SplashScreen_Load()
{
	currentSplashScreen = Factory_SpashScreen::CreateSpashScreen_Digipen();
}
void SplashScreen_Init()
{
	AEGfxSetBackgroundColor(0.00f, 0.00f, 0.00f);
	currentTimer = 0.0f;
	splashScreenStage = 0;
}
void SplashScreen_Update()
{
	currentTimer += g_dt;
	switch (currState)
	{
		case splashScreenState::preAnim:
			RenderingTricks::LightSpeedEffectIn(currentSplashScreen, currentTimer, postanimationTime[splashScreenStage], 0.5f
				, counter++, 100.0f, 100.0f, 0.0f, 0.0f, 0.02f, 60.0f);
			if (currentTimer > preanimationTime[splashScreenStage])
			{
				counter = 0;
				currentTimer = 0.0f;
				currState = splashScreenState::display;
			}
			break;
		case splashScreenState::display:
			if (currentTimer > displayTime[splashScreenStage])
			{
				currentTimer = 0.0f;
				currState = splashScreenState::postAnim;
			}
			break;
		case splashScreenState::postAnim:
			RenderingTricks::LightSpeedEffectOut(currentSplashScreen, currentTimer, counter++, 10.0f, 0.04f, -60.0f);
			if (currentTimer > postanimationTime[splashScreenStage])
			{
				counter = 0;
				currentTimer = 0.0f;
				++splashScreenStage;
				currState = splashScreenState::preAnim;
				SpashScreenIntervals();
			}
			break;
	}
}
void SplashScreen_Draw()
{
	Core::Get().Core_Render();
}
void SplashScreen_Free()
{
	AEGfxSetBackgroundColor(0.07f, 0.04f, 0.22f);
	AudioManager::UnLoadAllSounds();
}
void SplashScreen_Unload()
{
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}

void SpashScreenIntervals()
{
	switch (splashScreenStage)
	{
		case 1:
			Core::Get().EntityDestroyed(currentSplashScreen);
			currentSplashScreen = Factory_SpashScreen::CreateSpashScreen_MoonBase();
			break;
		default:
			AEGfxSetBackgroundColor(0.07f, 0.04f, 0.22f);								// Set Dark Purple BG 
			GSM_ChangeState(GS_MAINMENU);
			break;
	}
}
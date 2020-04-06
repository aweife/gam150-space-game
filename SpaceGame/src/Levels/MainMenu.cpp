/**********************************************************************************
* \file			MainMenu.cpp
* \brief		Game State for Main Menu
* \author		Jun Yi,			Chong,		50% Code Contribution
*       		Farzaana Binte,Roslan,		50% Code Contribution
*
*				Long Description
*				- Play, Options, Credits, Exit
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "MainMenu.h"
#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Managers/UIEventsManager.h"
#include "../Player/PlayerManager.h"
#include "../Managers/LevelManager.h"

struct MainMenu_Group
{
	ENTITY gameLogo;

	ENTITY playText;
	ENTITY optionText;
	ENTITY creditsText;
	ENTITY quitText;
	ENTITY tutorialPlanet;

	ENTITY toggleSoundTickbox;
	ENTITY toggleSoundTickbox_State;
	ENTITY toggleSoundText;
	ENTITY toggleFullscreenTickbox;
	ENTITY toggleFullscreenTickbox_State;
	ENTITY toggleFullscreenText;
};

mmStates currState = mmStates::MAIN;
float lightspeedTimer = 0.0f;
MainMenu_Group currentGroup;

void MainMenu_Load()
{
	//Special case.. since game window can resize
	Create_MainMenuInterface();
	PlayerManager::player = Factory::CreateMenuPlayer();
	Factory::CreateCamera(PlayerManager::player, false);

	Factory_Map::Generate_StarField();

	AEGfxSetCamPosition(0, 0);
}
void MainMenu_Init()
{
	//Restrict Player within menu...changed to wraping
	/*Factory::CreateLevelBoundary(g_WorldMaxX + 70.0f, 0, 150.0f, 2000);
	Factory::CreateLevelBoundary(g_WorldMinX - 70.0f, 0, 150.0f, 2000);
	Factory::CreateLevelBoundary(0, g_WorldMaxY + 70.0f, 2000, 150.0f);
	Factory::CreateLevelBoundary(0, g_WorldMinY - 70.0f, 2000, 150.0f);*/

}
void MainMenu_Update()
{
	if (lightspeedTimer > 0.0f)
	{
		lightspeedTimer -= g_dt;
		if (lightspeedTimer <= 0.0f)
		{
			LevelManager::SpeedChange_StarField(1/200.0f);
			lightspeedTimer = 0.0f;
		}
	}

	//AudioManager::Update();
	PlayerManager::Update();
	Core::Get().Core_Update();
}
void MainMenu_Draw()
{
	Core::Get().Core_Render();
}
void MainMenu_Free()
{

}
void MainMenu_Unload()
{
	LevelManager::Clear_StarField();
	Factory::RemoveCamera();
	PlayerManager::ResetPlayer(false);
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}

#include "../Systems/UISystem.h"
//Placed here since there is only one main menu
void Create_MainMenuInterface()
{
	// Main Section
	AEVec2 mmAnchor = ScreenBasedCoords(-0.45f, -0.75f, UI_ANCHOR::CENTER, true);
	currentGroup.playText =  Factory_UI::Create_MM_BeginCampaignUI({ mmAnchor.x, mmAnchor.y });
	mmAnchor = ScreenBasedCoords(-0.15f, -0.75f, UI_ANCHOR::CENTER, true);
	currentGroup.optionText = Factory_UI::Create_MM_OptionsUI({ mmAnchor.x, mmAnchor.y});
	mmAnchor = ScreenBasedCoords(0.15f, -0.75f, UI_ANCHOR::CENTER, true);
	currentGroup.creditsText = Factory_UI::Create_MM_CreditsUI({ mmAnchor.x , mmAnchor.y });
	mmAnchor = ScreenBasedCoords(0.45f, -0.75f, UI_ANCHOR::CENTER, true);
	currentGroup.quitText = Factory_UI::Create_MM_Quit({ mmAnchor.x, mmAnchor.y });

	AEVec2 mmAnchor2 = ScreenBasedCoords(0, 0.5f, UI_ANCHOR::CENTER, true);
	currentGroup.gameLogo = Factory_UI::Create_GameLogo( mmAnchor2, {400,240});
	currentGroup.tutorialPlanet = Factory::CreateTutorialPlanet(3, 400, 80, 300, 300);


	// Options Section
	mmAnchor = ScreenBasedCoords(0.0f, -0.75f, UI_ANCHOR::CENTER, true);
	AEVec2Set(&mmAnchor, mmAnchor.x - 5000, mmAnchor.y + 5000);
	Factory_UI::Create_MM_BackToMain(mmAnchor);
	
	// Mute sound
	mmAnchor = ScreenBasedCoords(-0.3f, 0.0f, UI_ANCHOR::CENTER, true);
	currentGroup.toggleSoundTickbox = Factory_UI::CreateUI_Option_TickBox_Sound(mmAnchor.x, mmAnchor.y, 40.0f, 0);
	currentGroup.toggleSoundTickbox_State = Core::Get().GetComponent<cUIElement>(currentGroup.toggleSoundTickbox)->_roleIndex;
	Core::Get().GetComponent<cSprite>(currentGroup.toggleSoundTickbox)->_colorTint.a = 0.0f;
	AEVec2Set(&mmAnchor, mmAnchor.x - 5000, mmAnchor.y + 5000);
	currentGroup.toggleSoundText = Factory_UI::CreateUI_Text(mmAnchor.x + 200.0f, mmAnchor.y, "Mute All Audio");

	// Toggle FullScreen
	mmAnchor = ScreenBasedCoords(-0.3f, -0.2f, UI_ANCHOR::CENTER, true);
	currentGroup.toggleFullscreenTickbox = Factory_UI::CreateUI_Option_TickBox_Fullscreen(mmAnchor.x, mmAnchor.y, 40.0f, 0);
	currentGroup.toggleFullscreenTickbox_State = Core::Get().GetComponent<cUIElement>(currentGroup.toggleFullscreenTickbox)->_roleIndex;
	Core::Get().GetComponent<cSprite>(currentGroup.toggleFullscreenTickbox)->_colorTint.a = 0.0f;
	AEVec2Set(&mmAnchor, mmAnchor.x - 5000, mmAnchor.y + 5000);
	currentGroup.toggleFullscreenText = Factory_UI::CreateUI_Text(mmAnchor.x + 200.0f, mmAnchor.y, "Windowed Mode");

	// Credits Section
	mmAnchor = ScreenBasedCoords(0.0f, -0.75f, UI_ANCHOR::CENTER, true);
	AEVec2Set(&mmAnchor, mmAnchor.x + 5000, mmAnchor.y + 5000);
	Factory_UI::Create_MM_BackToMain(mmAnchor);
	Factory::Create_Credits();
}

void Switch_MainMenuState(mmStates newState)
{
	LevelManager::SpeedChange_StarField(200.0f);
	lightspeedTimer = 0.25f;

	switch (newState)
	{
		case mmStates::MAIN:
			AEGfxSetCamPosition(0, 0);
			Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.x = -360;
			Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.y = -100;

			if (currState == mmStates::OPTIONS)
			{
				LevelManager::Move_StarField(5000, -5000);
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.x += 5000;
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.y += 5000;
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.x += -5000;
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.y += -5000;

				Core::Get().GetComponent<cSprite>(currentGroup.toggleSoundTickbox)->_colorTint.a = 0.0f;
				Core::Get().GetComponent<cSprite>(currentGroup.toggleFullscreenTickbox)->_colorTint.a = 0.0f;
				Core::Get().GetComponent<cSprite>(currentGroup.toggleSoundTickbox_State)->_colorTint.a = 0.0f;
				Core::Get().GetComponent<cSprite>(currentGroup.toggleFullscreenTickbox_State)->_colorTint.a = 0.0f;
			}
			else if (currState == mmStates::CREDITS)
			{
				LevelManager::Move_StarField(-5000, -5000);
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.x += -5000;
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.y += -5000;
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.x += -5000;
				Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.y += -5000;
				Core::Get().GetComponent<cSprite>(currentGroup.gameLogo)->_colorTint.a = 1.0f;
			}
			break;
		case mmStates::OPTIONS:		//Can only access from main menu
			AEGfxSetCamPosition(-5000, 5000);
			Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.x = -5000 - 360;
			Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.y = 5000 - 100;
			LevelManager::Move_StarField(-5000, 5000);
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.x -= 5000;
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.y -= 5000;
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.x += 5000;
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.y += 5000;

			Core::Get().GetComponent<cSprite>(currentGroup.toggleSoundTickbox)->_colorTint.a = 1.0f;
			Core::Get().GetComponent<cSprite>(currentGroup.toggleFullscreenTickbox)->_colorTint.a = 1.0f;
			Core::Get().GetComponent<cSprite>(currentGroup.toggleSoundTickbox_State)->_colorTint.a = g_isMute ? 1.0f : 0.0f;
			Core::Get().GetComponent<cSprite>(currentGroup.toggleFullscreenTickbox_State)->_colorTint.a = g_isFullScreen? 0.0f:1.0f;

			break;
		case mmStates::CREDITS:		//Can only access from main menu
			AEGfxSetCamPosition(5000, 5000);
			Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.x = 5000 - 360;
			Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position.y = 5000 - 100;
			LevelManager::Move_StarField(5000, 5000);
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.x += 5000;
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpX.y += 5000;
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.x += 5000;
			Core::Get().GetComponent<cWarping>(PlayerManager::player)->_warpY.y += 5000;
			Core::Get().GetComponent<cSprite>(currentGroup.gameLogo)->_colorTint.a = 0.0f;
			break;
	}
	currState = newState;
}
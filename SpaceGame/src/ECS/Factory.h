/*********************************************************************************
* \file			Factory.h
* \brief		Factory for creating entities in the game
* \author		Chong Jun Yi,			70% Code Contribution
* \author		Ang Wei Feng,			10% Code Contribution
* \author		Chong Jin Kiat,			10% Code Contribution
* \author		Farzaana Binte Roslan,	10% Code Contribution
*
*				Provide definitions of entities in the game. Responsible for
*				adding components to entities and initialising them.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "../Global_ECS.h"
#include "AEEngine.h"
#include "../Tools/MemoryLeak.h"
#include "../Components/ComponentList.h"

namespace Factory
{
	//Camera
	ENTITY CreateCamera(ENTITY player, bool dynamic = true);
	void RemoveCamera();

	//GameObjects
	ENTITY CreateMenuPlayer();
	ENTITY CreatePlayer(unsigned int layer);
	//ENTITY CreateEnemyObjective(ENTITY player, unsigned int layer, AEVec2 position);
	ENTITY SpawnObjective_Comrade(AEVec2 position, float startRotation, float rotationSpeed, AEVec2 size, int index);
	ENTITY SpawnLevel_End(AEVec2 position);
	ENTITY SpawnLevel_DeliveryEnd(AEVec2 position);
	ENTITY CreateWormhole(AEVec2 position, float rotSpeed = 5.0f, float rotStart = 0.0f, float uniformSize = 30.0f, int colorVariance = 0);
	ENTITY CreateTutorialPlanet(unsigned int layer, float posX, float posY, float scaleX, float scaleY);

	ENTITY SpawnDelivery(AEVec2 position, float startRotation, float rotationSpeed, AEVec2 size);
	ENTITY CreatePlanet1(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet2(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet3(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet4(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreateLevelBoundary(float posX, float posY, float scaleX, float scaleY);
	ENTITY CreateAsteroid1(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreateAsteroid2(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	void CreateBackground();
	void Create_Credits();

	ENTITY CreateBullet(float posX, float posY, AEVec2 velocityVector, AEVec2 dir, float rotation, OWNERTAG tag);
	ENTITY CreateBullet_LaserBeam(float posX, float posY, float rotation, OWNERTAG tag);
	
	ENTITY CreateHomingMissile(float posX, float posY, AEVec2 velocityVector, AEVec2 dir, float rotation, OWNERTAG tag, ENTITY target);

	//Debug graphics
	ENTITY CreateDebug_Arrow(AEVec2& pos, AEVec2& rot, float& scale);
	ENTITY CreateDebug_Line(AEVec2& start, AEVec2& end);
	ENTITY CreateDebug_Square(AEVec2& pos, float& rot, AEVec2& scale);
	ENTITY CreateDebug_Octagon(AEVec2& pos, float& rot, AEVec2& scale);
	ENTITY DebugVector_Velocity(ENTITY target);
	ENTITY DebugBoundingBox_Rigidbody(ENTITY target);

	// Particle systems
	ENTITY CreateParticleEmitter_MYFIRST();
	ENTITY CreateParticleEmitter_UPONIMPACT(cTransform* target);
	ENTITY CreateParticleEmitter_TRAIL(cTransform* tar);
	ENTITY CreateParticleEmitter_TRAILSTATIC(cTransform* tar);
	ENTITY CreateParticleEmitter_BOSSSPAWNSTATIC(cTransform* tar);
	ENTITY CreateParticleEmitter_OTHERSTATIC(cTransform* tar);

	ENTITY CreateParticleEmitter_DIVERGENCE(AEVec2 position, float radius, unsigned int count);
}

namespace Factory_ParticleFx
{
	ENTITY CreateParticleEmitter_FinaleMisson(AEVec2 position);
}


namespace Factory_UI
{
	//Game user interface
	ENTITY Create_GameLogo(AEVec2 position, AEVec2 scale);
	ENTITY Create_MM_BeginCampaignUI(AEVec2 position);
	ENTITY Create_MM_OptionsUI(AEVec2 position);
	ENTITY Create_MM_CreditsUI(AEVec2 position);
	ENTITY Create_MM_Quit(AEVec2 position);
	ENTITY Create_MM_BackToMain(AEVec2 position);

	void Create_PlayerUserInterface(unsigned int health = 3, unsigned int shield = 3);
	void CreateLowHealthInterface();
	void CreateShieldsDownInterface();
	void CreateBossIncomingInterface();
	ENTITY Create_SingleHealthBar(AEVec2 position, int i);
	ENTITY Create_SingleShieldBar(AEVec2 position, int i);
	ENTITY Create_ShieldBubble();
	ENTITY Create_ThrusterUI(AEVec2 position);
	ENTITY Create_LowHealthUI(AEVec2 position);
	ENTITY Create_ShieldsDownUI(AEVec2 position);
	ENTITY Create_BossIncomingUI(AEVec2 position);
	void Create_ChooseThree(AEVec2 centralPos, unsigned int reroll);
	void Create_ChoosableUpgrade(ENTITY entity);
	ENTITY Create_AIIndicator(ENTITY ai, AEVec2 aiDir, int aiType);

	ENTITY CreateUI_Objective_Base();
	ENTITY CreateUI_AddObjective(unsigned int index, const char* text);
	ENTITY CreateUI_AddObjective_Finale(unsigned int index, const char* text);

	void CreateUI_GameOver();
	void CreateUI_Pause();
	void CreateUI_GameWin();
	void  CreateUI_ExitConfirmation();
	void Create_InGameOptions();


	ENTITY CreateUI_Text(float posX, float posY, const char* text);
	ENTITY CreateUI_FloatingDamage(ENTITY target, int startHealth, int damageValue);

	ENTITY CreateUI_TickBox(float posX, float posY, float size, unsigned int layer = 0);
	ENTITY CreateUI_Option_TickBox_Sound(float posX, float posY, float size, unsigned int layer = 0);
	ENTITY CreateUI_Option_TickBox_Fullscreen(float posX, float posY, float size, unsigned int layer = 0);

	ENTITY CreateBackground_Load();

	// Level display
	ENTITY CreateUI_Level1Display();
	ENTITY CreateUI_Level2Display();
	ENTITY CreateUI_Level3Display();

}

namespace Factory_SpashScreen
{
	ENTITY CreateSpashScreen_Digipen();

	ENTITY CreateSpashScreen_MoonBase();
}

namespace Factory_Map
{
	void Generate_StarField();
	void Generate_PlanetField();
}

namespace Factory_AI
{
	ENTITY CreateEnemy1(ENTITY player, unsigned int layer, AEVec2 spawnPos);
	ENTITY CreateEnemy2(ENTITY player, unsigned int layer, AEVec2 spawnPos);
	ENTITY CreateEnemy1_2(ENTITY player, unsigned int layer, AEVec2 spawnPos); // Waves Enemies, tag: WAVE_ENEMIES
	ENTITY CreateEnemy2_2(ENTITY player, unsigned int layer, AEVec2 spawnPos); // Waves Enemies  tag: WAVE_ENEMIES
	ENTITY CreateEnemy2_3(ENTITY player, unsigned int layer, AEVec2 spawnPos); // Delivery Mission Enemies
	ENTITY CreateEscort(unsigned int layer, AEVec2 spawnPos);
	ENTITY CreateBoss(ENTITY player, unsigned int layer);
}
/**********************************************************************************
* \file			LevelManager.h
* \brief		Managers all levels.
* \author		Chong Jin Kiat, 90% Code Contribution
* \author		Chong Jun Yi, 10% Code Contribution
*
*				Manages spawnning of enemies, boss and objectives
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once

#include "AEEngine.h"	
#include "../Global_ECS.h"
#include <set>

const float OBJECTIVE_MIN_SPAWN_X = 20.0f;
const float OBJECTIVE_MIN_SPAWN_Y = 20.0f;

const float WAVE_ENEMY_MIN_SPAWN_X = 800.0f;
const float WAVE_ENEMY_MIN_SPAWN_Y = 800.0f;

const float DELIVERY_ENEMY_MIN_SPAWN_X = 400.0f;
const float DELIVERY_ENEMY_MIN_SPAWN_Y = 400.0f;

namespace LevelManager
{
	//Storage Containers
	extern std::set<ENTITY> starfield_Set;
	extern std::set<ENTITY> wavesEnemyList;

	//Misson Variables
	//Collectables
	extern bool objectiveComplete;
	extern bool spawnExit;
	//Delivery
	extern bool isCollected;
	extern float DeliveryEnemyTimer;
	extern int enemyObjectiveCount;
	extern bool enemyObjectiveComplete;
	extern bool isCollectedCompleted;
	extern bool endPortalSpawned;
	//Escort
	extern float escortEnemyTimer;
	extern bool isEscorting;

	// All 3 Levels Shared Functions
	void StartBossSpawnSequence();
	float RandomPos();
	void ClearLevel();

	// Level 1 Missions
	void Level1_Update();
	void Level1_Setup();
	void ObjectiveCompleteUpdate();
	//Check if collectable is out of screen
	void CheckOutOfScreen(ENTITY id);
	//Objectives
	void ClearObjective(ENTITY collectable);
	void ClearObjectiveAll();


	// Level 2 Missions
	void Level2_Setup();
	void Level2Update(AEVec2 playerPos, float DeliveryEnemySpawnTimer = 5.0f);
	void SpawnEnemyOnCollect(AEVec2 playerPos);
	void CheckDelivery();
	void ClearEnemy(ENTITY enemy);
	void CheckEnemyObjective();

	// Level 3 Missions
	void Level3_Setup();
	void Level3Update(ENTITY escort, float escortEnemySpawnTimer = 5.0f);
	void SpawnEnemyOnEscort(ENTITY escort, ENTITY player);
	void CheckEscort(AEVec2 escortPos, float checkPointX, float checkPointY);

	//Level 1 Spawning Functions
	void Level1_SetEnemySpawn(float randomLevel);
	void SetObjectiveSpawnArea();
	void SetObjectiveSpawn(float randomLevel);
	void ClearSpawnArea();

	//Manipulating StarField
	void Clear_StarField();
	void SpeedChange_StarField(float multiplier);
	void Move_StarField(float posX, float posY);

	namespace EnemySpawnManager
	{
		extern int enemyDestroyCounter;			// How many enemy DESTROYED
		extern int spawnedEnemy;				// How many enemy SPAWNED

		extern bool spawnEnemy;
		extern bool spawnBoss;					// Has boss BEEN Spawned

		//Timers
		extern float BossTimer;
		extern float WaveTimer;

		// Runs the countdown for boss to spawn
		void SpawnBoss(float spawnTimer = 3.0f);
		// Define the spawning area for enemy, around the player
		void EnemyWaveSpawnArea(AEVec2 spawnPos);
		// Check if next wave of enemy can be spawned (after a few seconds after all enemy defeated)
		void SpawnEnemyWavesTimer(AEVec2 playerPos, float spawnTimer = 5.0f);
		// Spawn enemy waves
		void SpawnEnemyWaves();

	}
}

struct objectSpawnArea
{
	float x;
	float y;
};




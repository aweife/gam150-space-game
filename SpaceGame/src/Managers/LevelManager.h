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
	// Level 1 Missions
	void Level1Update();
	void CheckOutOfScreen(ENTITY id);
	
	void SetObjectiveComplete();

	extern std::set<ENTITY> wavesEnemyList;

	float GetRandomPattern();

	float RandomPos();
	void SetObjectiveSpawnArea();

	void SetObjectiveSpawn(float randomLevel);
	void SetEnemySpawn(float randomLevel);
	void ClearSpawnArea();
	void Level1_Map();
	void ClearObjective(ENTITY collectable);
	void ClearObjectiveAll();

	namespace EnemySpawnManager
	{
		extern int enemyDestroyCounter;
		extern bool spawnEnemy;
		extern int spawnedEnemy;
		extern float BossTimer;
		extern float WaveTimer;
		extern bool spawnBoss;

		void SpawnBoss(ENTITY boss, float spawnTimer = 3.0f);
		void SpawnEnemyWavesTimer(AEVec2 playerPos, float spawnTimer = 5.0f);
		void SpawnEnemyWaves(AEVec2 playerPos);
		void EnemyWaveSpawnArea(AEVec2 spawnPos);
	}

	// Level 2 Missions
	void Level2Update(AEVec2 playerPos, float DeliveryEnemySpawnTimer = 5.0f);
	extern bool isCollected;
	extern float DeliveryEnemyTimer;
	void SpawnEnemyOnCollect(AEVec2 playerPos);

	// Level 3 Missions
	void Level3Update(AEVec2 escortPos, float escortEnemySpawnTimer = 5.0f);
	extern float escortEnemyTimer;

}

struct objectSpawnArea
{
	float x;
	float y;
};




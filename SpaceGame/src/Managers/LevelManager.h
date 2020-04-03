#pragma once

#include "AEEngine.h"	
#include "../Global_ECS.h"
#include <set>

const float OBJECTIVE_MIN_SPAWN_X = 20.0f;
const float OBJECTIVE_MIN_SPAWN_Y = 20.0f;

const float WAVE_ENEMY_MIN_SPAWN_X = 400.0f;
const float WAVE_ENEMY_MIN_SPAWN_Y = 400.0f;

namespace LevelManager
{
	void Update();
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

	bool isCollected;


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

	void DeliveryObjective();

}

struct objectSpawnArea
{
	float x;
	float y;
};




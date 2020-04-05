#pragma once

#include "AEEngine.h"	
#include "../Global_ECS.h"
#include <set>
const float MIN_SPAWN_X = 20.0f;
const float MIN_SPAWN_Y = 20.0f;

namespace LevelManager
{
	//Storage Containers
	extern std::set<ENTITY> starfield_Set;
	

	void Update();
	void CheckOutOfScreen(ENTITY id);
	
	void ClearLevel();
	void SetObjectiveComplete();
	void StartBossSpawnSequence();

	AEVec2 RandomEnemyPosition();
	AEVec2 RandomItemPosition();

	float GetRandomPattern();

	float RandomPos();
	void SetSpawnArea();

	void SetObjectiveSpawn(float randomLevel);
	void SetEnemySpawn(float randomLevel);
	void ClearSpawnArea();
	void Level1_Map();
	void ClearObjective(ENTITY collectable);
	void ClearObjectiveAll();

	void Clear_StarField();
	void SpeedChange_StarField(float multiplier);
	void Move_StarField(float posX, float posY);
}



struct objectSpawnArea1
{
	float x;
	float y;
};

struct objectSpawnArea2
{
	float x;
	float y;
};

struct objectSpawnArea3
{
	float x;
	float y;
};

struct objectSpawnArea4
{
	float x;
	float y;
};

struct objectSpawnArea5
{
	float x;
	float y;
};

struct objectSpawnArea6
{
	float x;
	float y;
};

struct objectSpawnArea7
{
	float x;
	float y;
};

struct objectSpawnArea8
{
	float x;
	float y;
};




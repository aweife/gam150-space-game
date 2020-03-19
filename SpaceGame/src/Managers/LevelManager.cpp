#include "LevelManager.h"
#include <list>
#include "../ECS/Factory.h"
#include "../Player/PlayerManager.h"

namespace LevelManager
{
	// Top Right, Top Left, Bottom Right, Bottom Left Spawn Areas
	objectSpawnArea1 topRightSpawnArea;
	objectSpawnArea2 topLeftSpawnArea;
	objectSpawnArea3 bottomLeftSpawnArea;
	objectSpawnArea4 bottomRightSpawnArea;

	// Top, Bottom, Left, Right Spawn Areas
	objectSpawnArea5 rightSpawnArea;
	objectSpawnArea6 leftSpawnArea;
	objectSpawnArea7 topSpawnArea;
	objectSpawnArea8 bottomSpawnArea;

	float GetRandomPattern()
	{
		float randomLevel = 0;
		randomLevel = floorf(AERandFloat() * 2.99f);

		return randomLevel;
	}

	std::list<AEVec2> randomEnemyPos
	{
		{0.0f, 0.0f},
		{100.0f, 100.0f},
		{90.0f,	90.0f},

		{-70.0f, 70.0f},
		{-90.0f, 100.0f},
		{-120.0f, 120.0f},
		{-105.0f, 110.0f},

		{ -70.0f, -70.0f },
		{ -90.0f, -100.0f },
		{ -120.0f, -120.0f },
		{ -105.0f, -110.0f },

		{ 80.0f, -80.0f },
		{ 100.0f, -100.0f },
		{ 90.0f, -90.0f }
	};

	std::list<AEVec2> randomItemPos
	{
		{110.0f, 110.0f},

		{-140.0f, 130.0f},

		{-140.0f, -130.0f},

		{ 70.0f, -70.0f }
	};


	AEVec2 RandomEnemyPosition()
	{
		AEVec2 position = randomEnemyPos.front();
		randomEnemyPos.pop_front();
		return position;
	}

	AEVec2 RandomItemPosition()
	{
		AEVec2 position = randomItemPos.front();
		randomItemPos.pop_front();
		return position;
	}

	void Level1_Map()
	{
		float randomLevel = GetRandomPattern();

		SetObjectiveSpawn(randomLevel);
		SetEnemySpawn(randomLevel);
	}


	void SetObjectiveSpawn(float randomLevel)
	{
		SetSpawnArea();
		AEVec2 spawnPos;
		AEVec2 objectiveSize;
		AEVec2Set(&objectiveSize, 50.0f, 50.0f);

		float randomSpawnArea = randomLevel;
		//float randomRotation = AERandFloat() * 360.0f;
		float rotationSpeed = 5.0f;

		switch (static_cast<int>(randomSpawnArea))
		{
		case 0:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, 60.0f, rotationSpeed, objectiveSize, 0);
			spawnPos.x = topLeftSpawnArea.x + RandomPos();
			spawnPos.y = topLeftSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, -120.0f, rotationSpeed, objectiveSize, 0);
			spawnPos.x = bottomSpawnArea.x + RandomPos();
			spawnPos.y = bottomSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, 240.0f, rotationSpeed, objectiveSize, 0);

			ClearSpawnArea();
			break;

		case 1:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, 60.0f, rotationSpeed, objectiveSize, 0);
			spawnPos.x = leftSpawnArea.x + RandomPos();
			spawnPos.y = leftSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, -120.0f, rotationSpeed, objectiveSize, 0);
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, 240.0f, rotationSpeed, objectiveSize, 0);

			ClearSpawnArea();
			break;

		case 2:
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, 60.0f, rotationSpeed, objectiveSize, 0);
			spawnPos.x = bottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = bottomLeftSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, -120.0f, rotationSpeed, objectiveSize, 0);
			spawnPos.x = topSpawnArea.x + RandomPos();
			spawnPos.y = topSpawnArea.y + RandomPos();
			// Spawn Objective;
			Factory::SpawnObjective_Comrade(spawnPos, 240.0f, rotationSpeed, objectiveSize, 0);

			ClearSpawnArea();
			break;
		}
	}

	void SetEnemySpawn(float randomLevel)
	{
		SetSpawnArea();
		AEVec2 spawnPos;

		float randomSpawnArea = randomLevel;

		switch (static_cast<int>(randomSpawnArea))
		{
		case 0:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topLeftSpawnArea.x + RandomPos();
			spawnPos.y = topLeftSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = bottomSpawnArea.x + RandomPos();
			spawnPos.y = bottomSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);

			ClearSpawnArea();
			break;

		case 1:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = leftSpawnArea.x + RandomPos();
			spawnPos.y = leftSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);

			ClearSpawnArea();
			break;

		case 2:
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = bottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = bottomLeftSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topSpawnArea.x + RandomPos();
			spawnPos.y = topSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory::CreateEnemyObjective(PlayerManager::player, 2, spawnPos);

			ClearSpawnArea();
			break;
		}
	}



	void SetSpawnArea()
	{

		// Top Right Area
		topRightSpawnArea.x = AERandFloat() * 1000.0f + MIN_SPAWN_X;
		topRightSpawnArea.y = AERandFloat() * 1000.0f + MIN_SPAWN_Y;

		// Top Left Area
		topLeftSpawnArea.x = AERandFloat() * -800.0f + -MIN_SPAWN_X;
		topLeftSpawnArea.y = AERandFloat() * 800.0f + MIN_SPAWN_Y;

		//Bottom Left Area
		bottomLeftSpawnArea.x = AERandFloat() * -1200.0f + -MIN_SPAWN_X;
		bottomLeftSpawnArea.y = AERandFloat() * -1200.0f + -MIN_SPAWN_Y;

		//Bottom Right Area
		bottomRightSpawnArea.x = AERandFloat() * 800.0f + MIN_SPAWN_X;
		bottomRightSpawnArea.y = AERandFloat() * -800.0f + -MIN_SPAWN_Y;

		// Right Area
		rightSpawnArea.x = AERandFloat() * 1000.0f + MIN_SPAWN_X;
		rightSpawnArea.y = RandomPos();

		// Left Area
		leftSpawnArea.x = AERandFloat() * -800.0f + -MIN_SPAWN_X;
		leftSpawnArea.y = RandomPos();

		//Top Area
		topSpawnArea.x = RandomPos();
		topSpawnArea.y = AERandFloat() * 1200.0f + MIN_SPAWN_Y;

		//Bottom Area
		bottomSpawnArea.x = RandomPos();
		bottomSpawnArea.y = AERandFloat() * -800.0f + -MIN_SPAWN_Y;

	}

	void ClearSpawnArea()
	{
		// Setting spawn area back to zero
		topRightSpawnArea.x = 0.0f;
		topRightSpawnArea.y = 0.0f;

		topLeftSpawnArea.x = 0.0f;
		topLeftSpawnArea.y = 0.0f;

		bottomLeftSpawnArea.x = 0.0f;
		bottomLeftSpawnArea.y = 0.0f;

		bottomRightSpawnArea.x = 0.0f;
		bottomRightSpawnArea.y = 0.0f;

		rightSpawnArea.x = 0.0f;
		rightSpawnArea.y = 0.0f;

		leftSpawnArea.x = 0.0f;
		leftSpawnArea.y = 0.0f;

		topSpawnArea.x = 0.0f;
		topSpawnArea.y = 0.0f;

		bottomSpawnArea.x = 0.0f;
		bottomSpawnArea.y = 0.0f;
	}

	// To Random a Range between positive Y and negative Y
	float RandomPos()
	{
		float random = 0.0f;
		float randomPos = 0.0f;
		random = floorf(AERandFloat() * 1.99f);

		switch (static_cast<int>(random))
		{
			// Negative Y or X
		case 0:
			randomPos = AERandFloat() * -450.0f;
			break;
			// Positive Y or X
		case 1:
			randomPos = AERandFloat() * 450.0f;
			break;
		}
		return randomPos;
	}


	/*
	float randomOffSetX()
	{
		float spawnOffSetX = 0.0f;
		float random = 0.0f;
		random = floorf(AERandFloat() * 1.99f);

		if (spawnOffSetX == oldOffSetX)
		{
			switch (static_cast<int>(random))
			{
				// Negative X
			case 0:
				spawnOffSetX = AERandFloat() * -450.0f;
				break;
				// Positive X
			case 1:
				spawnOffSetX = AERandFloat() * 450.0f;
				break;
			}
		}
		else
		{
			oldOffSetX = spawnOffSetX;
			return spawnOffSetX;
		}

		return spawnOffSetX;
	}


	float randomOffSetY()
	{
		float spawnOffSetY = 0.0f;
		float random = 0.0f;
		random = floorf(AERandFloat() * 1.99f);

		if (spawnOffSetY == oldOffSetY)
		{
			switch (static_cast<int>(random))
			{
				// Negative X
			case 0:
				spawnOffSetX = AERandFloat() * -450.0f;
				break;
				// Positive X
			case 1:
				spawnOffSetX = AERandFloat() * 450.0f;
				break;
			}
		}
		else
		{
			oldOffSetY = spawnOffSetY;
			return spawnOffSetY;
		}

		return spawnOffSetY;
	}
	*/




}


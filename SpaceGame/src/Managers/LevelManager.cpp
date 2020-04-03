#include "LevelManager.h"
#include "../ECS/Factory.h"
#include "../Player/PlayerManager.h"

#include "../ECS/Core.h"
#include "../Systems/UISystem.h"							//Spawn Ai Indicators
#include "../Tools/Editor.h"
#include "../Levels/UpgradeLevel.h"
#include "../Managers/GameStateManager.h"

#include <iostream>
namespace LevelManager
{
	// Top Right, Top Left, Bottom Right, Bottom Left Spawn Areas for Objectives
	objectSpawnArea topRightSpawnArea;
	objectSpawnArea topLeftSpawnArea;
	objectSpawnArea bottomLeftSpawnArea;
	objectSpawnArea bottomRightSpawnArea;

	// Top, Bottom, Left, Right Spawn Areas for Objectives
	objectSpawnArea rightSpawnArea;
	objectSpawnArea leftSpawnArea;
	objectSpawnArea topSpawnArea;
	objectSpawnArea bottomSpawnArea;

	objectSpawnArea enemyTopRightSpawnArea;
	objectSpawnArea enemyTopLeftSpawnArea;
	objectSpawnArea enemyBottomLeftSpawnArea;
	objectSpawnArea enemyBottomRightSpawnArea;

	// Enemy Waves
	std::set<ENTITY> wavesEnemyList;

	// Objective 
	std::set<ENTITY> collectableList;
	bool objectiveComplete;
	bool upgradePhase;

	// Delivery
	isCollected = false;



	namespace EnemySpawnManager
	{
		int enemyDestroyCounter = 0;
		bool spawnEnemy = false;
		int spawnedEnemy = 0;
		float BossTimer = 0.0f;
		float WaveTimer = 0.0f;
		bool spawnBoss = false;
	}
	void Update()
	{
		if (upgradePhase) return;

		for (std::set<ENTITY>::const_iterator it = collectableList.begin(); it != collectableList.end(); ++it)
		{
			CheckOutOfScreen(*it);
		}
		//Hacks...by right need to check if enemy killed or collectable done
		if (objectiveComplete)
		{
			//Factory_UI::Create_ChooseThree({ 0,0 });
			loadingForNextLevel = GS_LEVEL1;
			GSM_ChangeState(GS_UPGRADE);
			upgradePhase = true;
		}
	}
	void CheckOutOfScreen(ENTITY id)
	{
		cTransform* self = Core::Get().GetComponent<cTransform>(id);
		
		AEVec2 cameraPosition = { 0 };
		AEGfxGetCamPosition(&cameraPosition.x, &cameraPosition.y);

		if (!(self->_position.x > cameraPosition.x - g_WorldMaxX && self->_position.x < cameraPosition.x + g_WorldMaxX
			&& self->_position.y > cameraPosition.y - g_WorldMaxY && self->_position.y < cameraPosition.y + g_WorldMaxY))
		{
			AEVec2 relativeDirection;
			AEVec2Sub(&relativeDirection, &self->_position, &cameraPosition);
			std::shared_ptr<UISystem> uiSys(std::static_pointer_cast<UISystem>(Core::Get().GetSystem<UISystem>()));

			//@TED later just change the last variable for different enemy type
			uiSys->Check_AIIndicatorExist(id, relativeDirection, 0); //Under UI System
		}
	}

	//HACKS
	void SetObjectiveComplete()
	{
		//objectiveComplete = true;
	}

	float GetRandomPattern()
	{
		float randomLevel = 0;
		randomLevel = floorf(AERandFloat() * 2.99f);

		return randomLevel;
	}

	void Level1_Map()
	{
		float randomLevel = GetRandomPattern();

		//3 objectives
		SetObjectiveSpawn(randomLevel);
		SetEnemySpawn(randomLevel);
		objectiveComplete = false;
		upgradePhase = false;
	}


	void SetObjectiveSpawn(float randomLevel)
	{
		SetObjectiveSpawnArea();
		AEVec2 spawnPos;
		AEVec2 objectiveSize;
		AEVec2Set(&objectiveSize, 50.0f, 50.0f);

		float randomSpawnArea = randomLevel;
		//float randomRotation = AERandFloat() * 360.0f;
		float rotationSpeed = 5.0f;

		ENTITY collectable;
		switch (static_cast<int>(randomSpawnArea))
		{
		case 0:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, 60.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			spawnPos.x = topLeftSpawnArea.x + RandomPos();
			spawnPos.y = topLeftSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, -120.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			spawnPos.x = bottomSpawnArea.x + RandomPos();
			spawnPos.y = bottomSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, 240.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			ClearSpawnArea();
			break;

		case 1:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, 60.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			spawnPos.x = leftSpawnArea.x + RandomPos();
			spawnPos.y = leftSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, -120.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, 240.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			ClearSpawnArea();
			break;

		case 2:
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, 60.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			spawnPos.x = bottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = bottomLeftSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, -120.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			spawnPos.x = topSpawnArea.x + RandomPos();
			spawnPos.y = topSpawnArea.y + RandomPos();
			// Spawn Objective;
			collectable = Factory::SpawnObjective_Comrade(spawnPos, 240.0f, rotationSpeed, objectiveSize, 0);
			collectableList.insert(collectable);

			ClearSpawnArea();
			break;
		}
	}

	void SetEnemySpawn(float randomLevel)
	{
		SetObjectiveSpawnArea();
		AEVec2 spawnPos;

		float randomSpawnArea = randomLevel;

		switch (static_cast<int>(randomSpawnArea))
		{
		case 0:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy1(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy1(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy2(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topLeftSpawnArea.x + RandomPos();
			spawnPos.y = topLeftSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy2(PlayerManager::player, 2, spawnPos);
			spawnPos.x = bottomSpawnArea.x + RandomPos();
			spawnPos.y = bottomSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy1(PlayerManager::player, 2, spawnPos);

			ClearSpawnArea();
			break;

		case 1:
			spawnPos.x = topRightSpawnArea.x + RandomPos();
			spawnPos.y = topRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy1(PlayerManager::player, 2, spawnPos);
			spawnPos.x = leftSpawnArea.x + RandomPos();
			spawnPos.y = leftSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy2(PlayerManager::player, 2, spawnPos);
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy1(PlayerManager::player, 2, spawnPos);

			ClearSpawnArea();
			break;

		case 2:
			spawnPos.x = bottomRightSpawnArea.x + RandomPos();
			spawnPos.y = bottomRightSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy1(PlayerManager::player, 2, spawnPos);
			spawnPos.x = bottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = bottomLeftSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy2(PlayerManager::player, 2, spawnPos);
			spawnPos.x = topSpawnArea.x + RandomPos();
			spawnPos.y = topSpawnArea.y + RandomPos();
			// Spawn Enemy;
			Factory_AI::CreateEnemy2(PlayerManager::player, 2, spawnPos);

			ClearSpawnArea();
			break;
		}
	}

	void SetObjectiveSpawnArea()
	{

		// Top Right Area
		topRightSpawnArea.x = AERandFloat() * 1000.0f + OBJECTIVE_MIN_SPAWN_X;
		topRightSpawnArea.y = AERandFloat() * 1000.0f + OBJECTIVE_MIN_SPAWN_Y;

		// Top Left Area
		topLeftSpawnArea.x = AERandFloat() * -800.0f + -OBJECTIVE_MIN_SPAWN_X;
		topLeftSpawnArea.y = AERandFloat() * 800.0f + OBJECTIVE_MIN_SPAWN_Y;

		//Bottom Left Area
		bottomLeftSpawnArea.x = AERandFloat() * -1200.0f + -OBJECTIVE_MIN_SPAWN_X;
		bottomLeftSpawnArea.y = AERandFloat() * -1200.0f + -OBJECTIVE_MIN_SPAWN_Y;

		//Bottom Right Area
		bottomRightSpawnArea.x = AERandFloat() * 800.0f + OBJECTIVE_MIN_SPAWN_X;
		bottomRightSpawnArea.y = AERandFloat() * -800.0f + -OBJECTIVE_MIN_SPAWN_Y;

		// Right Area
		rightSpawnArea.x = AERandFloat() * 1000.0f + OBJECTIVE_MIN_SPAWN_X;
		rightSpawnArea.y = RandomPos();

		// Left Area
		leftSpawnArea.x = AERandFloat() * -800.0f + -OBJECTIVE_MIN_SPAWN_X;
		leftSpawnArea.y = RandomPos();

		//Top Area
		topSpawnArea.x = RandomPos();
		topSpawnArea.y = AERandFloat() * 1200.0f + OBJECTIVE_MIN_SPAWN_Y;

		//Bottom Area
		bottomSpawnArea.x = RandomPos();
		bottomSpawnArea.y = AERandFloat() * -800.0f + -OBJECTIVE_MIN_SPAWN_Y;

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

	void ClearObjective(ENTITY collectable)
	{
		collectableList.erase(collectable);

		if (collectableList.size() == 0)
			objectiveComplete = true;

		printf("Objectives Left: %d\n", collectableList.size());
	}

	void ClearObjectiveAll()
	{
		collectableList.clear();
	}


	void EnemySpawnManager::SpawnBoss(ENTITY boss, float spawnTimer)
	{
		if (!spawnBoss)
		{
			BossTimer += g_dt;

			if (BossTimer >= spawnTimer)
			{
				boss = Factory_AI::CreateBoss(PlayerManager::player, 2);
				spawnBoss = true;
			}
		}
	}

	void EnemySpawnManager::EnemyWaveSpawnArea(AEVec2 playerPos)
	{
		enemyTopRightSpawnArea.x = playerPos.x + (AERandFloat() * 400.0f) + WAVE_ENEMY_MIN_SPAWN_X;
		enemyTopRightSpawnArea.y = playerPos.y + (AERandFloat() * 400.0f) + WAVE_ENEMY_MIN_SPAWN_Y;

		enemyTopLeftSpawnArea.x = playerPos.x - (AERandFloat() * 400.0f) - WAVE_ENEMY_MIN_SPAWN_X;
		enemyTopLeftSpawnArea.y = playerPos.y + (AERandFloat() * 400.0f) + WAVE_ENEMY_MIN_SPAWN_Y;

		enemyBottomLeftSpawnArea.x = playerPos.x - (AERandFloat() * 400.0f) - WAVE_ENEMY_MIN_SPAWN_X;
		enemyBottomLeftSpawnArea.y = playerPos.y - (AERandFloat() * 400.0f) - WAVE_ENEMY_MIN_SPAWN_Y;

		enemyBottomRightSpawnArea.x = playerPos.x + (AERandFloat() * 400.0f) + WAVE_ENEMY_MIN_SPAWN_X;
		enemyBottomRightSpawnArea.y = playerPos.y - (AERandFloat() * 400.0f) - WAVE_ENEMY_MIN_SPAWN_Y;
	}

	void EnemySpawnManager::SpawnEnemyWavesTimer(AEVec2 playerPos, float spawnTimer)
	{
		AEVec2 spawnPos;
		ENTITY wavesEnemies;
		EnemySpawnManager::EnemyWaveSpawnArea(playerPos);
		std::cout << wavesEnemyList.size() << std::endl;

		if (spawnEnemy)
		{
			WaveTimer += g_dt;

			std::cout << WaveTimer << std::endl;
			if (WaveTimer >= spawnTimer && wavesEnemyList.size() == 0)
			{

				SpawnEnemyWaves(playerPos);
				spawnEnemy = false;
				WaveTimer = 0.0f;
			}
		}

		if(wavesEnemyList.size() == 0)
		{
			std::cout << "did it come here" << std::endl;
			spawnEnemy = true;
		}
	}

	void EnemySpawnManager::SpawnEnemyWaves(AEVec2 playerPos)
	{
		int randomEnemySpawn = 0;
		AEVec2 spawnPos;
		ENTITY wavesEnemies;

		randomEnemySpawn = floorf(AERandFloat() * 2.99f);

		switch (randomEnemySpawn)
		{
		case 0:
			spawnPos.x = enemyTopRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy4(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);
			break;

		case 1:
			spawnPos.x = enemyTopLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy4(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy4(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);
			break;

		case 2:
			spawnPos.x = enemyBottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy4(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);
			break;

		case 3:
			spawnPos.x = enemyBottomRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy4(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);
			break;
		}
	}

	void DeliveryObjective()
	{
		
	}

}


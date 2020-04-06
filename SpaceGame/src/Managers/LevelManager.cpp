#include "LevelManager.h"
#include "../ECS/Factory.h"
#include "../Player/PlayerManager.h"

#include "../ECS/Core.h"
#include "../Systems/UISystem.h"							//Spawn Ai Indicators
#include "../Tools/Editor.h"
#include "../Levels/UpgradeLevel.h"
#include "../Managers/GameStateManager.h"
#include "../Levels/Level3.h"
#include <iostream>

namespace LevelManager
{
	//Storage Containers
	std::set<ENTITY> starfield_Set;
	std::set<ENTITY> wavesEnemyList;			// Enemy Waves
	std::set<ENTITY> collectableList;			// Objective for Level 1

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

	// Spawn AREA FOR ENEMY WAVES
	objectSpawnArea enemyTopRightSpawnArea;
	objectSpawnArea enemyTopLeftSpawnArea;
	objectSpawnArea enemyBottomLeftSpawnArea;
	objectSpawnArea enemyBottomRightSpawnArea;

	ENTITY exitId;							// Wormhole ENTITY
	GAMESTATE nextGameState;

	//Objectives for Level 1
	bool objectiveComplete = false;
	bool spawnExit = false;
	unsigned int enemySpawned1 = 0;

	// Delivery for Level 2
	bool isCollected = false;
	float DeliveryEnemyTimer = 0.0f;
	unsigned int eliminatedCount = 0;
	unsigned int enemySpawned2 = 0;
	int enemyObjectiveCount = 0;
	bool enemyObjectiveComplete = false;
	bool isCollectedCompleted = false;
	bool endPortalSpawned = false;

	// Escort for Level 3s
	float escortEnemyTimer = 0.0f;
	bool isEscorting = true;
	bool defeatBoss = false;
	unsigned int enemySpawned3 = 0;


	// Boss Spawn Sequence
	bool arrival1, arrival2, arrival3;
	float bossTimer = 0.0f;
	const float bossArrivalTime = 5.0f;
	AEVec2 bossSpawnPos;

	// Shared Functions
	void StartBossSpawnSequence()
	{
		objectiveComplete = true;
		if (currentState != GS_LEVEL3)
		{
			spawnExit = true;
			exitId = Factory::SpawnLevel_End({ 0.0f, -1000.0f });
		}

		// Init spawn sequence
		Factory::CreateParticleEmitter_DIVERGENCE({ 0.0f,0.0f }, 300.0f, 5, bossArrivalTime);
		arrival1 = arrival2 = arrival3 = false;
		bossTimer = bossArrivalTime / 3.0f;

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
		default:
			break;
		}
		return randomPos;
	}

	void ClearLevel()
	{
		if (currentState == GS_LEVEL3)
		{
			Factory_UI::CreateUI_GameWin();
			return;
		}
		loadingForNextLevel = nextGameState;
		GSM_ChangeState(GS_UPGRADE);
		exitId = 0;
		objectiveComplete = false;
		spawnExit = false;
	}

	void Level1_Update()
	{
		// Checking for collectable completion
		if (objectiveComplete)
		{
			ObjectiveCompleteUpdate();
		}

		// Check if Collectables are out of screen
		for (std::set<ENTITY>::const_iterator it = collectableList.begin(); it != collectableList.end(); ++it)
		{
			CheckOutOfScreen(*it);
		}
		if (PlayerManager::player)
		{
			AEVec2 playerPos = Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position;

			if (enemySpawned1 > 3)
			{
				EnemySpawnManager::SpawnEnemyWavesTimer(playerPos);
			}
		}
	}

	void Level1_Setup()
	{
		float randomLevel = floorf(AERandFloat() * 2.99f);

		//3 objectives
		SetObjectiveSpawn(randomLevel);
		// 3 - 5 enemies
		Level1_SetEnemySpawn(randomLevel);

		objectiveComplete = false;
		spawnExit = false;
		nextGameState = GS_LEVEL2;
		enemySpawned1 = 0;
		bossSpawnPos = { 0.0f,0.0f };
	}

	void ObjectiveCompleteUpdate()
	{
		if(spawnExit)
			CheckOutOfScreen(exitId);

		// Boss spawn sequence
		if (arrival1 && arrival2 && arrival3) return;
		bossTimer -= g_dt;

		if (bossTimer < 0.0f)
		{
			bossTimer = bossArrivalTime / 3.0f;

			if (!arrival1)
			{
				arrival1 = true;
				Factory::CreateParticleEmitter_DIVERGENCE({ 0.0f,0.0f }, 250.0f, 10, bossArrivalTime / 2.0f);
			}
			else if (!arrival2)
			{
				arrival2 = true;
				Factory::CreateParticleEmitter_DIVERGENCE({ 0.0f,0.0f }, 150.0f, 20, bossArrivalTime/ 3.0f);
			}
			else
			{
				arrival3 = true;
				Factory_AI::CreateBoss(bossSpawnPos, PlayerManager::player, 2);
			}
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

			// Infinite range as long as Out Of Screen
			uiSys->Check_IndicatorExist(id, relativeDirection, 5); //Under UI System
		}
	}

	void ClearObjective(ENTITY collectable)
	{
		collectableList.erase(collectable);

		if (collectableList.size() == 0)
		{
			StartBossSpawnSequence();
		}
	}

	void ClearObjectiveAll()
	{
		collectableList.clear();
	}

	void Level2_Setup()
	{
		nextGameState = GS_LEVEL3;
		eliminatedCount = 0;
		enemySpawned2 = 0;
		wavesEnemyList.clear();
		spawnExit = false;
		isCollected = false;

		bossSpawnPos = { 0.0f,0.0f };
	}

	// Start spawning enemies after delivery is collected
	void Level2Update(AEVec2 playerPos, float DeliveryEnemySpawnTimer)
	{
		if (isCollected)
		{
			if (objectiveComplete)
			{
				ObjectiveCompleteUpdate();
			}

			if (spawnExit)
			{
				CheckOutOfScreen(exitId);
			}


			//Straight away spawn boss upon collection
			if (/*eliminatedCount >= 10 && */!objectiveComplete)
			{
				objectiveComplete = true;
			}

			DeliveryEnemyTimer += g_dt;

			//Spawn enemy at fixed intervals
			if (DeliveryEnemyTimer >= DeliveryEnemySpawnTimer)
			{
				if (enemySpawned2 < 15)
				{
					SpawnEnemyOnCollect(playerPos);
				}
				DeliveryEnemyTimer = 0.0f;
			}

			if (isCollectedCompleted && !endPortalSpawned)
			{
				spawnExit = true;
				exitId = Factory::SpawnLevel_End({ 0.0f, 500.0f });
				endPortalSpawned = true;
			}

		}
	}

	void CheckEnemyObjective()
	{
		++enemyObjectiveCount;
		if (enemyObjectiveCount >= 10)
		{
			std::cout << "did it enemyobjectivecomplete" << std::endl;
			enemyObjectiveComplete = true;
		}
	}

	void CheckDelivery()
	{
		isCollected = true;

		exitId = Factory::SpawnLevel_DeliveryEnd({ 1000.0f, 0.0f });

	}

	void ClearEnemy(ENTITY enemy)
	{
		if (wavesEnemyList.find(enemy) != wavesEnemyList.end())
		{
			++eliminatedCount;
			if (nextGameState == GS_LEVEL2)
			{
				--enemySpawned1;
			}
			else if (nextGameState == GS_LEVEL3)
			{
				--enemySpawned2;
			}
			else if (nextGameState == GS_MAINMENU)
			{
				--enemySpawned3;
			}
		}
		wavesEnemyList.erase(enemy);
	}

	void Level3_Setup()
	{
		nextGameState = GS_MAINMENU;
		isEscorting = true;
		wavesEnemyList.clear();
		defeatBoss = false;
		enemySpawned3 = 0;

		bossSpawnPos = { 200.0f,0.0f };
	}

	void Level3Update(ENTITY escort, float escortEnemySpawnTimer)
	{
		if (objectiveComplete)
		{
			ObjectiveCompleteUpdate();

			if (defeatBoss)
			{
				if (!spawnExit)
				{
					spawnExit = true;
					exitId = Factory::SpawnLevel_End({ 0.0f, 0.0f });
				}
			}
		}

		if (escort == 0) return;

		AEVec2 escortPos = Core::Get().GetComponent<cTransform>(escort)->_position;

		if (isEscorting)
		{
			escortEnemyTimer += g_dt;

			CheckEscort(escortPos, 800.0f, 0.0f);

			if (escortEnemyTimer >= escortEnemySpawnTimer)
			{
				if (enemySpawned3 < 8)
				{
					SpawnEnemyOnEscort(escort, PlayerManager::player);
				}

				escortEnemyTimer = 0.0f;
			}
		}
	}

	void CheckEscort(AEVec2 escortPos, float checkPointX, float checkPointY)
	{
		UNREFERENCED_PARAMETER(checkPointY);
		if (escortPos.x >= checkPointX && isEscorting)
		{
			// Do UI
			isEscorting = false;
			SetMissionStatus(true);
			EscortDeath(true);
			StartBossSpawnSequence();
		}
	}

	void DefeatBoss()
	{
		defeatBoss = true;
	}

	void SpawnEnemyOnCollect(AEVec2 playerPos)
	{
		AEVec2 spawnPos;

		int numberOfDeliveryEnemies = static_cast<int>(floorf(AERandFloat() * 2.99f));
		ENTITY enemy;

		switch (numberOfDeliveryEnemies)
		{
		case 0:
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned2;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f - DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			break;
		case 1:
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			break;
		case 2:
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f - DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f - DELIVERY_ENEMY_MIN_SPAWN_Y;
			Factory_AI::CreateEnemy2_3(PlayerManager::player, 2, spawnPos);
			++enemySpawned2;
			break;
		default:
			break;
		}
	}

	void SpawnEnemyOnEscort(ENTITY escort, ENTITY player)
	{
		AEVec2 spawnPos;
		AEVec2 playerPos = Core::Get().GetComponent<cTransform>(player)->_position;
		int numberOfDeliveryEnemies = static_cast<int>(floorf(AERandFloat() * 2.99f));

		ENTITY enemy;

		switch (numberOfDeliveryEnemies)
		{
		case 0:
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			++enemySpawned3;
			wavesEnemyList.insert(enemy);
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f - DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			break;
		case 1:
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			break;
		case 2:
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f - DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			spawnPos.x = playerPos.x + AERandFloat() * 300.0f + DELIVERY_ENEMY_MIN_SPAWN_X;
			spawnPos.y = playerPos.y + AERandFloat() * 300.0f - DELIVERY_ENEMY_MIN_SPAWN_Y;
			enemy = Factory_AI::CreateEnemy2_3(escort, 2, spawnPos);
			wavesEnemyList.insert(enemy);
			++enemySpawned3;
			break;
		default:
			break;
		}
	}

	// Level 1 Spawning Function

	void Level1_SetEnemySpawn(float randomLevel)
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
		default:
			break;
		}
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
		collectableList.clear();

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
		default:
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

	void Clear_StarField()
	{
		//Leave the actual entity destruction to Core
		starfield_Set.clear();
	}

	void SpeedChange_StarField(float multiplier)
	{
		//Leave the actual entity destruction to Core
		for (auto const& entity : starfield_Set)
		{
			Core::Get().GetComponent<cRigidBody>(entity)->_velocity *= multiplier;
			Core::Get().GetComponent<cRigidBody>(entity)->_velocityCap *= multiplier;
		}
	}

	void Move_StarField(float posX, float posY)
	{
		for (auto const& entity : starfield_Set)
		{
			Core::Get().GetComponent<cTransform>(entity)->_position.x += posX;
			Core::Get().GetComponent<cTransform>(entity)->_position.y += posY;
			Core::Get().GetComponent<cWarping>(entity)->_warpX.x += posX;
			Core::Get().GetComponent<cWarping>(entity)->_warpX.y += posX;
			Core::Get().GetComponent<cWarping>(entity)->_warpY.x += posY;
			Core::Get().GetComponent<cWarping>(entity)->_warpY.y += posY;
		}
	}

	namespace EnemySpawnManager
	{
		int enemyDestroyCounter = 0;			// How many enemy DESTROYED
		int spawnedEnemy = 0;					// How many enemy SPAWNED

		bool spawnEnemy = false;				// Am I allowed to spawn the next enemy
		bool spawnBoss = false;					// Has boss BEEN Spawned

		//Timers
		float BossTimer = 0.0f;
		float WaveTimer = 0.0f;
	}

	// Runs the countdown for boss to spawn
	void EnemySpawnManager::SpawnBoss(float spawnTimer)
	{
		if (!spawnBoss)
		{
			BossTimer += g_dt;

			if (BossTimer >= spawnTimer)
			{
				// This line is removed by JY since will have to check with TED
				//boss = Factory_AI::CreateBoss(PlayerManager::player, 2);
				spawnBoss = true;
			}
		}
	}

	// Define the spawning area for enemy, around the player
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

	// Check if next wave of enemy can be spawned (after a few seconds after all enemy defeated )
	void EnemySpawnManager::SpawnEnemyWavesTimer(AEVec2 playerPos, float spawnTimer)
	{
		EnemySpawnManager::EnemyWaveSpawnArea(playerPos);

		if (spawnEnemy)
		{
			WaveTimer += g_dt;

			// If timer interval is reached and all waves enemy is defeated, spawn the next enemy 
			if (WaveTimer >= spawnTimer && wavesEnemyList.size() == 0)
			{
				SpawnEnemyWaves();
				spawnEnemy = false;
				WaveTimer = 0.0f;
			}
		}

		if (wavesEnemyList.size() == 0)
		{
			spawnEnemy = true;
		}
	}

	// Spawn enemy waves
	void EnemySpawnManager::SpawnEnemyWaves()
	{
		int randomEnemySpawn = 0;
		AEVec2 spawnPos;
		ENTITY wavesEnemies;

		randomEnemySpawn = static_cast<int>(floorf(AERandFloat() * 2.99f));

		switch (randomEnemySpawn)
		{
		case 0:
			spawnPos.x = enemyTopRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy2_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			enemySpawned1 += 3;
			break;

		case 1:
			spawnPos.x = enemyTopLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy2_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyTopLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyTopLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy2_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			enemySpawned1 += 3;
			break;

		case 2:
			spawnPos.x = enemyBottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy2_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomLeftSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomLeftSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			enemySpawned1 += 3;
			break;

		case 3:
			spawnPos.x = enemyBottomRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy2_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			spawnPos.x = enemyBottomRightSpawnArea.x + RandomPos();
			spawnPos.y = enemyBottomRightSpawnArea.y + RandomPos();
			wavesEnemies = Factory_AI::CreateEnemy1_2(PlayerManager::player, 2, spawnPos);
			wavesEnemyList.insert(wavesEnemies);

			enemySpawned1 += 3;
			break;

		default:
			break;
		}
	}

}


#include "LevelManager.h"
#include <list>
#include <set>
#include "../ECS/Factory.h"
#include "../Player/PlayerManager.h"

#include "../ECS/Core.h"
#include "../Systems/UISystem.h"							//Spawn Ai Indicators
#include "../Tools/Editor.h"
#include "../Levels/UpgradeLevel.h"
#include "../Managers/GameStateManager.h"

namespace LevelManager
{
	std::set<ENTITY> starfield_Set;

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

	std::set<ENTITY> collectableList;
	
	bool objectiveComplete;
	bool upgradePhase;
	bool spawnExit;
	ENTITY exitId;

	void Update()
	{
		if (upgradePhase) return;

		for (std::set<ENTITY>::const_iterator it = collectableList.begin(); it != collectableList.end(); ++it)
		{
			CheckOutOfScreen(*it);
		}

		// If objective complete, spawn level end
		if (objectiveComplete)
			SetObjectiveComplete();
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
		if (spawnExit)
		{
			CheckOutOfScreen(exitId);
		}
		else
		{
			spawnExit = true;
			exitId = Factory::SpawnLevel_End({ 0.0f, -1000.0f });

			StartBossSpawnSequence();
		}
	}

	void StartBossSpawnSequence()
	{
		Factory::CreateParticleEmitter_DIVERGENCE({ 0.0f,-100.0f }, 100.0f, 10);
	}

	void ClearLevel()
	{
		//Factory_UI::Create_ChooseThree({ 0,0 });
		loadingForNextLevel = GS_LEVEL1;
		GSM_ChangeState(GS_UPGRADE);
		upgradePhase = true;
	}

	float GetRandomPattern()
	{
		float randomLevel = 0;
		randomLevel = floorf(AERandFloat() * 2.99f);

		return randomLevel;
	}

	//std::list<AEVec2> randomEnemyPos
	//{
	//	{0.0f, 0.0f},
	//	{100.0f, 100.0f},
	//	{90.0f,	90.0f},

	//	{-70.0f, 70.0f},
	//	{-90.0f, 100.0f},
	//	{-120.0f, 120.0f},
	//	{-105.0f, 110.0f},

	//	{ -70.0f, -70.0f },
	//	{ -90.0f, -100.0f },
	//	{ -120.0f, -120.0f },
	//	{ -105.0f, -110.0f },

	//	{ 80.0f, -80.0f },
	//	{ 100.0f, -100.0f },
	//	{ 90.0f, -90.0f }
	//};

	//std::list<AEVec2> randomItemPos
	//{
	//	{110.0f, 110.0f},

	//	{-140.0f, 130.0f},

	//	{-140.0f, -130.0f},

	//	{ 70.0f, -70.0f }
	//};


	/*AEVec2 RandomEnemyPosition()
	{
		AE_ASSERT(randomEnemyPos.size() > 0 && "No more enemy position to churn out");

		AEVec2 position = randomEnemyPos.front();
		randomEnemyPos.pop_front();
		return position;
	}

	AEVec2 RandomItemPosition()
	{
		AE_ASSERT(randomItemPos.size() > 0 && "No more item position to churn out");

		AEVec2 position = randomItemPos.front();
		randomItemPos.pop_front();
		return position;
	}*/

	void Level1_Map()
	{
		float randomLevel = GetRandomPattern();

		//3 objectives
		SetObjectiveSpawn(randomLevel);
		SetEnemySpawn(randomLevel);
		objectiveComplete = false;
		upgradePhase = false;
		spawnExit = false;
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
		SetSpawnArea();
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

	void ClearObjective(ENTITY collectable)
	{
		collectableList.erase(collectable);

		if (collectableList.size() == 0)
			objectiveComplete = true;

		printf("Objectives Left: %zd\n", collectableList.size());
	}

	void ClearObjectiveAll()
	{
		collectableList.clear();
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
}


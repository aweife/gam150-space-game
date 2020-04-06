/*********************************************************************************
* \file			Factory.cpp
* \brief		Factory for creating entities in the game
* \author		Chong Jun Yi,			25% Code Contribution
* \author		Ang Wei Feng,			25% Code Contribution
* \author		Chong Jin Kiat,			25% Code Contribution
* \author		Farzaana Binte Roslan,	25% Code Contribution
*
*				Provide definitions of entities in the game. Responsible for
*				adding components to entities and initialising them.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Factory.h"
#include "Core.h"
#include "../Global.h"
#include "../Systems/SystemList.h"
#include "../Managers/ManagerList.h"		
#include "../Global_Graphics.h"	
#include "../Player/PlayerManager.h"
namespace Factory
{
	// Create a dynamic camera to follow player & screenshake
	ENTITY CreateCamera(ENTITY player, bool dynamic)
	{
		ENTITY cameraID = Core::Get().CreateEntity();
		cTransform* playerTransform = Core::Get().GetComponent<cTransform>(player);
		cRigidBody* playerRigidBody = Core::Get().GetComponent<cRigidBody>(player);

		float followSpeed = 300.0f;
		if (playerRigidBody)
		{
			if (playerRigidBody->_velocityCap > 50.0f)
			{
				followSpeed = playerRigidBody->_velocityCap;
			}
		}
		Core::Get().AddComponent<cTransform>(cameraID, new cTransform());
		Core::Get().AddComponent<cCamera>(cameraID, new cCamera(playerTransform, 400.0f, dynamic));
		CameraManager::AssignNewCam(cameraID);

		return cameraID;
	}

	void RemoveCamera()
	{
		CameraManager::RemoveCurrCam();
	}

	ENTITY CreateMenuPlayer()
	{
		ENTITY player = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(player, new cTransform({ -360, -100 }, PI * 1 / 9, { 50,50 }));
		Core::Get().AddComponent<cSprite>(player, new cSprite(player, "Square Mesh", "Player_1", 2));
		
		//No Hard Velocity Cap so player can move freely
		Core::Get().AddComponent<cRigidBody>(player, new cRigidBody(3.0f, 0.0f, 300.0, 3.0f, 2.0f));
		Core::Get().GetComponent<cRigidBody>(player)->_tag = COLLISIONTAG::PLAYER_MENU;
		Core::Get().AddComponent<cCollision>(player, new cCollision);
		//Enable player to move and shoot in main menu
		Core::Get().AddComponent<cSpaceShip>(player, new cSpaceShip{ false, 2.0f, WeaponMode::WEAPONMODE_RANGE });
		Core::Get().AddComponent<cRangeWeapon>(player, new cRangeWeapon{ OWNERTAG::PLAYER, WeaponType::pistol, 1.0f, 0.25f });
		Core::Get().AddComponent<cWarping>(player, new cWarping({ g_WorldMinX -25, g_WorldMaxX +25}, { g_WorldMinY -25,g_WorldMaxY +25}));

		CreateParticleEmitter_OTHERSTATIC(Core::Get().GetComponent<cTransform>(player));
		return player;
	}

	ENTITY CreatePlayer(unsigned int layer)
	{
		ENTITY player = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(player, new cTransform({ 0,0 }, 0.0f, {50.0f, 50.0f}));
		Core::Get().AddComponent<cSprite>(player, new cSprite(player, "Square Mesh", "Player_1", layer));
		Core::Get().AddComponent<cRigidBody>(player, new cRigidBody(3.0f, 0.0f, 75.0, 5.0f, 2.0f));
		Core::Get().GetComponent<cRigidBody>(player)->_velocityHardCap = 250;
		Core::Get().GetComponent<cRigidBody>(player)->_tag = COLLISIONTAG::PLAYER;
		Core::Get().AddComponent<cCollision>(player, new cCollision);
		Core::Get().GetComponent<cCollision>(player)->_bbShape = ColliderShape::RECTANGLE;
		
		if (!PlayerManager::playerProgressInit)
		{
			PlayerManager::CreatePlayerWeapon();
		}

		Core::Get().AddComponent<cSpaceShip>(player, new cSpaceShip{ PlayerManager::playerSpaceshipProgression });
		Core::Get().AddComponent<cRangeWeapon>(player, new cRangeWeapon{ PlayerManager::playerRangeProgression });
		//Core::Get().AddComponent<cRangeWeapon>(player, new cRangeWeapon(OWNERTAG::PLAYER, WeaponType::laser, 999.0f, 0.0f, 1));
		Core::Get().AddComponent<cMeleeWeapon>(player, new cMeleeWeapon{ PlayerManager::playerMeleeProgression });
		//Core::Get().AddComponent<cHealth>(player, new cHealth(2.0f, 3.0f, 2.0f, 3.0f, 5.0f,2.0f));
		Core::Get().AddComponent<cHealth>(player, new cHealth{ PlayerManager::playerHealthProgression });
		Factory_UI::Create_ShieldBubble();

		// Debug
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(player);					//For Collision

		return player;
	}

	ENTITY SpawnObjective_Comrade(AEVec2 position, float startRotation, float rotationSpeed, AEVec2 size, int index)
	{
		UNREFERENCED_PARAMETER(index);
		ENTITY objective = Core::Get().CreateEntity();

		Core::Get().AddComponent<cTransform>(objective, new cTransform(position, startRotation, size));
		Core::Get().AddComponent<cSprite>(objective, new cSprite(objective, "Square Mesh", "Player_1", 21));

		Core::Get().AddComponent<cTimeline>(objective, new cTimeline(g_appTime, g_appTime + rotationSpeed, true));
		Core::Get().AddComponent<cRigidBody>(objective, new cRigidBody(30.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().AddComponent<cCollision>(objective, new cCollision);

		Core::Get().AddComponent<cAI>(objective, new cAI{ objective, OBJECTIVE });
		Core::Get().GetComponent<cAI>(objective)->_currentState.states.emplace<aiIdle>();

		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(objective)->_rotation, Core::Get().GetComponent<cTimeline>(objective));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(objective)->_rotation, Core::Get().GetComponent<cTimeline>(objective), 5.0f, Core::Get().GetComponent<cTransform>(objective)->_rotation + 2 * PI);

		Core::Get().GetComponent<cRigidBody>(objective)->_tag = COLLISIONTAG::OBJECTIVE; // testing collision
		Core::Get().GetComponent<cCollision>(objective)->_bbShape = ColliderShape::RECTANGLE_OBB;

		return objective;
	}

	
	ENTITY SpawnLevel_End(AEVec2 position)
	{
		ENTITY exit = CreateWormhole(position, 5.0f, 0.0f, 30.0f);
		// Objective will check if player remains in range for a few seconds
		Core::Get().AddComponent<cAI>(exit, new cAI{ exit, LEVEL_END });
		Core::Get().GetComponent<cAI>(exit)->_currentState.states.emplace<aiIdle>();

		return exit;
	}

	ENTITY SpawnLevel_DeliveryEnd(AEVec2 position)
	{
		ENTITY wormhole = CreateWormhole(position, 5.0f, 0.0f, 30.0f, 2);
		Core::Get().AddComponent<cRigidBody>(wormhole, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(wormhole)->_tag = COLLISIONTAG::DELIVERYCOMPLETE;
		Core::Get().AddComponent<cCollision>(wormhole, new cCollision);

		return wormhole;
	}


	ENTITY SpawnDelivery(AEVec2 position, float startRotation, float rotationSpeed, AEVec2 size)
	{
		ENTITY delivery = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(delivery, new cTransform(position, startRotation, size));
		Core::Get().AddComponent<cRigidBody>(delivery, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(delivery)->_tag = COLLISIONTAG::DELIVERY;

		Core::Get().AddComponent<cSprite>(delivery, new cSprite(delivery, "Square Mesh", "Delivery", 2));

		Core::Get().AddComponent<cAI>(delivery, new cAI{ delivery, DELIVERY });
		Core::Get().GetComponent<cAI>(delivery)->_currentState.states.emplace<aiIdle>();

		Core::Get().AddComponent<cTimeline>(delivery, new cTimeline(g_appTime, g_appTime + rotationSpeed, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(delivery)->_rotation, Core::Get().GetComponent<cTimeline>(delivery));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(delivery)->_rotation, Core::Get().GetComponent<cTimeline>(delivery), 5.0f, Core::Get().GetComponent<cTransform>(delivery)->_rotation + 2 * PI);

		//Core::Get().AddComponent<cRigidBody>(delivery, new cRigidBody(30.0f, 0.0f, 0.0f, 0.0f));
		//Core::Get().AddComponent<cCollision>(delivery, new cCollision);
		//Core::Get().GetComponent<cRigidBody>(delivery)->_tag = COLLISIONTAG::DELIVERY; // testing collision
		//Core::Get().GetComponent<cCollision>(delivery)->_bbShape = ColliderShape::RECTANGLE_OBB;

		return delivery;
	}


	//Reused for main menu and level exit
	ENTITY CreateWormhole(AEVec2 position, float rotSpeed, float rotStart, float uniformSize, int colorVariance)
	{
		AEVec2 size{uniformSize, uniformSize};

		rotSpeed *= 1.0f;
		AEVec2Scale(&size, &size, 4.0f);

		//Sort the entity to create layering
		ENTITY exit3 = Core::Get().CreateEntity();
		ENTITY exit2 = Core::Get().CreateEntity();
		ENTITY exit1 = Core::Get().CreateEntity();
		ENTITY* arrayToSort[3] = { &exit3, &exit2, &exit1 };
		Core::Get().SortEntity(arrayToSort);

		//Outer Wormhole
		Core::Get().AddComponent<cTransform>(exit3, new cTransform(position, rotStart, size));
		Core::Get().AddComponent<cTimeline>(exit3, new cTimeline(g_appTime, g_appTime + rotSpeed, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(exit3)->_rotation, Core::Get().GetComponent<cTimeline>(exit3));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_rotation, Core::Get().GetComponent<cTimeline>(exit3)
			, 0.0f, Core::Get().GetComponent<cTransform>(exit3)->_rotation);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_rotation, Core::Get().GetComponent<cTimeline>(exit3)
			, rotSpeed, Core::Get().GetComponent<cTransform>(exit3)->_rotation + 2.0f * PI);
		//Scale to animate
		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.x, Core::Get().GetComponent<cTimeline>(exit3));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.x, Core::Get().GetComponent<cTimeline>(exit3)
			, 0.0f, Core::Get().GetComponent<cTransform>(exit3)->_scale.x);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.x, Core::Get().GetComponent<cTimeline>(exit3)
			, rotSpeed /2, Core::Get().GetComponent<cTransform>(exit3)->_scale.x * 1.2f);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.x, Core::Get().GetComponent<cTimeline>(exit3)
			, rotSpeed, Core::Get().GetComponent<cTransform>(exit3)->_scale.x);

		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.y, Core::Get().GetComponent<cTimeline>(exit3));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.y, Core::Get().GetComponent<cTimeline>(exit3)
			, 0.0f, Core::Get().GetComponent<cTransform>(exit3)->_scale.y);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.y, Core::Get().GetComponent<cTimeline>(exit3)
			, rotSpeed /2, Core::Get().GetComponent<cTransform>(exit3)->_scale.y * 1.2f);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit3)->_scale.y, Core::Get().GetComponent<cTimeline>(exit3)
			, rotSpeed, Core::Get().GetComponent<cTransform>(exit3)->_scale.y);

		rotSpeed *= 2.0f;
		AEVec2Scale(&size, &size, 0.75f);

		
		Core::Get().AddComponent<cTransform>(exit2, new cTransform(position, rotStart, size));
		Core::Get().AddComponent<cTimeline>(exit2, new cTimeline(g_appTime, g_appTime + rotSpeed, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(exit2)->_rotation, Core::Get().GetComponent<cTimeline>(exit2));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit2)->_rotation, Core::Get().GetComponent<cTimeline>(exit2)
			,  0.0f, Core::Get().GetComponent<cTransform>(exit2)->_rotation);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit2)->_rotation, Core::Get().GetComponent<cTimeline>(exit2)
			, rotSpeed, Core::Get().GetComponent<cTransform>(exit2)->_rotation - 2.0f * PI);

		rotSpeed *= 0.3f;
		AEVec2Scale(&size, &size, 0.5f);

		//small white 
		
		Core::Get().AddComponent<cTransform>(exit1, new cTransform(position, rotStart, size));
		//Looping Rotation
		Core::Get().AddComponent<cTimeline>(exit1, new cTimeline(g_appTime, g_appTime + rotSpeed, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cTransform>(exit1)->_rotation, Core::Get().GetComponent<cTimeline>(exit1));
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit1)->_rotation, Core::Get().GetComponent<cTimeline>(exit1)
			, 0.0f, Core::Get().GetComponent<cTransform>(exit1)->_rotation);
		AddNewNode_Float(&Core::Get().GetComponent<cTransform>(exit1)->_rotation, Core::Get().GetComponent<cTimeline>(exit1)
			, rotSpeed, Core::Get().GetComponent<cTransform>(exit1)->_rotation + 2.0f * PI);

		// Layering
		Core::Get().AddComponent<cSprite>(exit3, new cSprite(exit3, "Square Mesh", "Exit_3", 21));
		Core::Get().AddComponent<cSprite>(exit2, new cSprite(exit2, "Square Mesh", "Exit_2", 21));
		Core::Get().AddComponent<cSprite>(exit1, new cSprite(exit1, "Square Mesh", "Exit_1", 21));
		if (colorVariance == 1)//red
		{
			Core::Get().GetComponent<cSprite>(exit3)->_colorTint = Core::Get().GetComponent<cSprite>(exit2)->_colorTint
				= Core::Get().GetComponent<cSprite>(exit1)->_colorTint = { 1.0f, 0.0f, 0.0f, 1.0f };
		}
		else if (colorVariance == 2)
		{
			Core::Get().GetComponent<cSprite>(exit3)->_colorTint = Core::Get().GetComponent<cSprite>(exit2)->_colorTint
				= Core::Get().GetComponent<cSprite>(exit1)->_colorTint = { 1.0f, 1.0f, 0.8f, 1.0f };
		}
		else if (colorVariance == 3)	//yellow
		{
			Core::Get().GetComponent<cSprite>(exit3)->_colorTint = Core::Get().GetComponent<cSprite>(exit2)->_colorTint
				= Core::Get().GetComponent<cSprite>(exit1)->_colorTint = { 1.0f, 1.0f, 0.0f, 1.0f };
		}
		else if (colorVariance == 4)
		{
			Core::Get().GetComponent<cSprite>(exit3)->_colorTint = Core::Get().GetComponent<cSprite>(exit2)->_colorTint
				= Core::Get().GetComponent<cSprite>(exit1)->_colorTint = { 1.0f, 0.0f, 1.0f, 1.0f };
		}


		return exit1;
	}

	ENTITY CreateTutorialPlanet(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY planet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(planet, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "Square Mesh", "Tutorial_planet", layer));

		return planet;
	}

	ENTITY CreatePlanet1(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY planet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(planet, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "Square Mesh", "Planet_1", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody(1000.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(planet)->_velocity = 0;
		//Core::Get().AddComponent<cCollision>(planet, new cCollision);

		return planet;
	}

	ENTITY CreatePlanet2(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY planet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(planet, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "Square Mesh", "Planet_2", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody(1000.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(planet)->_velocity = 0;

		return planet;
	}
	ENTITY CreatePlanet3(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY planet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(planet, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "Square Mesh", "Planet_3", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody(1000.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(planet)->_velocity = 0;
		//Core::Get().AddComponent<cCollision>(planet, new cCollision);

		return planet;
	}
	ENTITY CreatePlanet4(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY planet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(planet, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "Square Mesh", "Planet_4", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody(1000.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(planet)->_velocity = 0;
		//Core::Get().AddComponent<cCollision>(planet, new cCollision);

		return planet;
	}

	ENTITY CreateLevelBoundary(float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPosition, newScale;
		AEVec2Set(&newPosition, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY asteroid = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(asteroid, new cTransform(newPosition, 0, newScale));
		Core::Get().AddComponent<cRigidBody>(asteroid, new cRigidBody(500.f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(asteroid)->_tag = COLLISIONTAG::PLANET_ASTEROID;
		Core::Get().AddComponent<cCollision>(asteroid, new cCollision);

		return asteroid;
	}

	ENTITY CreateAsteroid1(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPosition, newScale;
		AEVec2Set(&newPosition, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY asteroid = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(asteroid, new cTransform(newPosition, 0, newScale));
		Core::Get().AddComponent<cSprite>(asteroid, new cSprite(asteroid, "Square Mesh", "Asteroid_1", layer));
		Core::Get().AddComponent<cRigidBody>(asteroid, new cRigidBody(500.f, 0.0f, 0.0f, 0.0f));
		Core::Get().AddComponent<cCollision>(asteroid, new cCollision);
		Core::Get().GetComponent<cRigidBody>(asteroid)->_velocity = 50.0f;
		Core::Get().GetComponent<cRigidBody>(asteroid)->_tag = COLLISIONTAG::PLANET_ASTEROID;


		return asteroid;
	}

	ENTITY CreateAsteroid2(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPosition, newScale;
		AEVec2Set(&newPosition, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY asteroid = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(asteroid, new cTransform(newPosition, 0, newScale));
		Core::Get().AddComponent<cSprite>(asteroid, new cSprite(asteroid, "Square Mesh", "Asteroid_2", layer));
		Core::Get().AddComponent<cRigidBody>(asteroid, new cRigidBody(500.f, 0.0f, 0.0f, 0.0f));
		Core::Get().AddComponent<cCollision>(asteroid, new cCollision);
		Core::Get().GetComponent<cRigidBody>(asteroid)->_velocity = 50.0f;
		Core::Get().GetComponent<cRigidBody>(asteroid)->_tag = COLLISIONTAG::PLANET_ASTEROID;

		return asteroid;
	}

	void CreateBackground()
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, 0, 0);
		AEVec2Set(&newScale, 1300, 1000);
		ENTITY background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 7));
	}

	void Create_Credits()
	{
		ENTITY credits1 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits1, new cTransform({ 4550,5200 }, 0, { 550, 200 }));
		Core::Get().AddComponent<cSprite>(credits1, new cSprite(credits1, "Square Mesh", "Credits_1", 2));

		ENTITY credits2 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits2, new cTransform({ 5050, 5200 }, 0, { 300, 150 }));
		Core::Get().AddComponent<cSprite>(credits2, new cSprite(credits2, "Square Mesh", "Credits_2", 2));

		ENTITY credits3 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits3, new cTransform({ 5555, 5200 }, 0, { 250, 250 }));
		Core::Get().AddComponent<cSprite>(credits3, new cSprite(credits3, "Square Mesh", "Credits_3", 2));

		ENTITY credits4 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits4, new cTransform({ 4650, 4900 }, 0, { 200, 100 }));
		Core::Get().AddComponent<cSprite>(credits4, new cSprite(credits4, "Square Mesh", "Credits_4", 2));

		ENTITY credits5 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits5, new cTransform({ 5350, 4900 }, 0, { 400, 200 }));
		Core::Get().AddComponent<cSprite>(credits5, new cSprite(credits5, "Square Mesh", "Credits_5", 2));
	}

	ENTITY CreateBullet(float posX, float posY, AEVec2 velocityVector, AEVec2 dir, float rotation, OWNERTAG tag)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, 10, 40);

		ENTITY bullet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(bullet, new cTransform(newPostion, rotation, newScale));
		Core::Get().AddComponent<cSprite>(bullet, new cSprite(bullet, "Square Mesh", "Bullet_1", 2));
		Core::Get().AddComponent<cRigidBody>(bullet, new cRigidBody(30.0f, 500.0f, 500.0f));
		Core::Get().AddComponent<cCollision>(bullet, new cCollision);
		Core::Get().AddComponent<cProjectile>(bullet, new cProjectile(2.0f, 2.0f, bulletType::normal));
		Core::Get().GetComponent<cCollision>(bullet)->_bbShape = ColliderShape::RECTANGLE_OBB;
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(bullet);					//For Collision

		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityDirection = dir;
		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityVector = velocityVector;
		if (tag == OWNERTAG::PLAYER)
			Core::Get().GetComponent<cRigidBody>(bullet)->_tag = COLLISIONTAG::BULLET_PLAYER;
		else
			Core::Get().GetComponent<cRigidBody>(bullet)->_tag = COLLISIONTAG::BULLET;

		AudioManager::PlayOneShot("res/SFX/Confirm.wav");

		return bullet;
	}

	ENTITY CreateHomingMissile(float posX, float posY, AEVec2 velocityVector, AEVec2 dir, float rotation, OWNERTAG tag, ENTITY target)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, 40, 40);

		ENTITY bullet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(bullet, new cTransform(newPostion, rotation, newScale));
		Core::Get().AddComponent<cSprite>(bullet, new cSprite(bullet, "Square Mesh", "Bullet_2", 2));
		Core::Get().AddComponent<cRigidBody>(bullet, new cRigidBody(30.0f, 500.0f, 500.0f));
		Core::Get().AddComponent<cCollision>(bullet, new cCollision);
		Core::Get().AddComponent<cProjectile>(bullet, new cProjectile(2.0f, 2.0f, bulletType::normal, true));
		Core::Get().GetComponent<cCollision>(bullet)->_bbShape = ColliderShape::RECTANGLE_OBB;
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(bullet);					//For Collision

		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityDirection = dir;
		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityVector = velocityVector;
		if (tag == OWNERTAG::PLAYER)
			Core::Get().GetComponent<cRigidBody>(bullet)->_tag = COLLISIONTAG::BULLET_PLAYER;
		else
			Core::Get().GetComponent<cRigidBody>(bullet)->_tag = COLLISIONTAG::BULLET;
		AudioManager::PlayOneShot("res/SFX/Confirm.wav");

		Core::Get().GetComponent<cProjectile>(bullet)->_targetId = target;

		return bullet;
	}

	ENTITY CreateBullet_LaserBeam(float posX, float posY, float rotation, OWNERTAG tag)
	{
		ENTITY bullet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(bullet, new cTransform({ posX, posY }, rotation, { 1280, 4 }));
		Core::Get().AddComponent<cSprite>(bullet, new cSprite(bullet, "LaserBeam", "Texture_Fill", 2));
		Core::Get().GetComponent<cSprite>(bullet)->_colorTint = { 1.0f, 0, 0, 1.0f };
		Core::Get().GetComponent<cSprite>(bullet)->_UVOffset.x = 0.4f;
		Core::Get().AddComponent<cRigidBody>(bullet, new cRigidBody(0.0f, 0.0f, 0.0f));
		Core::Get().AddComponent<cCollision>(bullet, new cCollision);

		Core::Get().GetComponent<cCollision>(bullet)->_bbShape = ColliderShape::RAYCAST;
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(bullet);					//For Collision

		Core::Get().AddComponent<cProjectile>(bullet, new cProjectile(999.0f, 999.0f, bulletType::laser));
		if (tag == OWNERTAG::PLAYER)
			Core::Get().GetComponent<cRigidBody>(bullet)->_tag = COLLISIONTAG::BULLET_PLAYER;
		else
			Core::Get().GetComponent<cRigidBody>(bullet)->_tag = COLLISIONTAG::BULLET;

		return bullet;
	}

	ENTITY CreateDebug_Arrow(AEVec2& pos, AEVec2& rot, float& scale)
	{
		ENTITY debug = Core::Get().CreateEntity();
		Core::Get().AddComponent<cDebugTools>(debug, new cDebugTools(pos, rot, scale, scale, DEBUGTYPE::DEBUG_ARROW, "Arrow Line"));
		return debug;
	}

	//Lines are anchored from one dynamic point to another dynamic point
	ENTITY CreateDebug_Line(AEVec2& start, AEVec2& end)
	{
		//Realistically rot and scale wont be used
		ENTITY debug = Core::Get().CreateEntity();
		Core::Get().AddComponent<cDebugTools>(debug, new cDebugTools(start, defaultAEVec2, defaultFloat, defaultFloat,
			DEBUGTYPE::DEBUG_LINE, "Simple Line", end));
		return debug;

		//SAMPLE CODE
		/*Factory::CreateDebug_Line(Core::Get().GetComponent<cTransform>(PlayerManager::player)->_position
		, Core::Get().GetComponent<cTransform>(enemy)->_position);*/
	}

	ENTITY CreateDebug_Square(AEVec2& pos, float& rot, AEVec2& scale)
	{
		//Realistically rot and scale wont be used
		ENTITY debug = Core::Get().CreateEntity();
		Core::Get().AddComponent<cDebugTools>(debug, new cDebugTools(pos, rot, scale.x, scale.y, DEBUGTYPE::DEBUG_SQUARE, "Square Frame"));
		return debug;
	}

	ENTITY CreateDebug_Octagon(AEVec2& pos, float& rot, AEVec2& scale)
	{
		//Realistically rot and scale wont be used
		ENTITY debug = Core::Get().CreateEntity();
		Core::Get().AddComponent<cDebugTools>(debug, new cDebugTools(pos, rot, scale.x, scale.y, DEBUGTYPE::DEBUG_OCTAGON, "Octagon Frame"));
		return debug;
	}

	ENTITY DebugVector_Velocity(ENTITY target)
	{
		AEVec2& rPlayerPos = Core::Get().GetComponent<cTransform>(target)->_position;
		AEVec2& rPlayerVelocityRot = Core::Get().GetComponent<cRigidBody>(target)->_velocityDirection;
		float& rVelocity = Core::Get().GetComponent<cRigidBody>(target)->_velocity;

		return CreateDebug_Arrow(rPlayerPos, rPlayerVelocityRot, rVelocity);
	}

	ENTITY DebugBoundingBox_Rigidbody(ENTITY target)
	{
		cCollision* collisionComponent = Core::Get().GetComponent<cCollision>(target);
		cTransform* transformComponent = Core::Get().GetComponent<cTransform>(target);
		ENTITY boundingBox = 0;

		AE_ASSERT(collisionComponent != nullptr && "No collision component on called object");

		if (collisionComponent->_bbShape == ColliderShape::RECTANGLE || collisionComponent->_bbShape == ColliderShape::RECTANGLE_OBB)
		{
			boundingBox = Factory::CreateDebug_Square(transformComponent->_position, transformComponent->_rotation,
				transformComponent->_scale);
			return boundingBox;
		}
		else if (collisionComponent->_bbShape == ColliderShape::CIRCLE)
		{
			boundingBox = Factory::CreateDebug_Octagon(transformComponent->_position, transformComponent->_rotation,
				transformComponent->_scale);
			return boundingBox;
		}
		else if (collisionComponent->_bbShape == ColliderShape::RAYCAST)
		{
			return 0;
		}

		AE_ASSERT(boundingBox != 0 && "No COLLIDERSHAPE specified on collision component");
		return 0;
	}

	ENTITY CreateParticleEmitter_MYFIRST()
	{
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform({ 0, 0 }, 0.0f, { 1,1 }));
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0,0 }, 160.0f, 0.2f, 0.4f, 1.0f, 1));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 3;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", { 1.0f, 1.0f, 1.0f, 0.35f },
			{ 20,20 }, 1.0f, { 0.0f,0.0f }, { 0.0f, 1.0f }, 5.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 40,40 }, { 70, 70 }, VARIANCETYPE::RANDOM_UNIFORM, { -1,-1 }, { 1,1 }, VARIANCETYPE::RANDOM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(2.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(0.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 150, 150 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 120, 120 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 100, 100 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 40, 40 });
		return emitter;
	}

	ENTITY CreateParticleEmitter_UPONIMPACT(cTransform* target)
	{
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform({ target->_position.x, target->_position.y }, 0.0f, { 1,1 }));
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0.0f, 0.0f }, 60.0f, 0.2f, 0.4f, 1.0f, 1));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 3;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", { 1.0f, 1.0f, 1.0f, 0.35f },
			{ 20,20 }, 1.0f, { 0.0f, 0.0f }, { 0.0f, 1.0f }, 5.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 40,40 }, { 70, 70 }, VARIANCETYPE::RANDOM_UNIFORM, { -1,-1 }, { 1,1 }, VARIANCETYPE::RANDOM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 0.75f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 0.15f, 0.1f, 0.1f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 0.4f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(2.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(0.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 100, 100 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 80, 80 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 60, 60 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 20, 20 });
		return emitter;
	}

	ENTITY CreateParticleEmitter_TRAIL(cTransform* tar)
	{
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform({ tar->_position.x, tar->_position.y }, 0.0f, { 1,1 }));
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0.0f,0.0f }, 10.0f, 0.2f, 0.4f, 1.0f, 1));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 3;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", { 1.0f, 1.0f, 1.0f, 0.35f },
			{ 20,20 }, 1.0f, { 0.0f,0.0f }, { 0.0f, 1.0f }, 5.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 20,20 }, { 40, 40 }, VARIANCETYPE::RANDOM_UNIFORM, { -1,-1 }, { 1,1 }, VARIANCETYPE::RANDOM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(0.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(0.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 30, 30 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 20, 20 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 10, 10 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 5, 5 });
		return emitter;
	}

	ENTITY CreateParticleEmitter_TRAILSTATIC(cTransform* tar)
	{
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform({ tar->_position.x, tar->_position.y }, 0.0f, { 1,1 }));
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ -10.0f,-2.0f }, 10.0f, 0.1f, 0.2f, 999.0f, 3,
			0.0f, 0.0f, 2.0f));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 90;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", { 1.0f, 0.5f, 0.0f, 0.5f },
			{ 20,20 }, 2.0f, { 0.0f,0.0f }, { -1.0f, -0.3f }, 100.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 2,2 }, { 28, 28 }, VARIANCETYPE::RANDOM_UNIFORM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(50.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(0.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 28, 28 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 20, 20 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 10, 10 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 5, 5 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 1, 1 });
		return emitter;
	}

	ENTITY CreateParticleEmitter_BOSSSPAWNSTATIC(cTransform* tar)
	{
		UNREFERENCED_PARAMETER(tar);
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform({ -100.0f, -100.0f }, 0.0f, { 1,1 }));
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0.0f, 0.0f }, 5.0f, 0.1f, 0.2f, 20.0f, 3, 
			0.0f, 0.0f, 2.0f));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 70;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", { 0.0f, 0.0f, 1.0f, 0.5f },
			{ 20,20 }, 2.0f, { 0.0f,0.0f }, { -1.0f, -0.3f }, 50.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 28,28 }, { 28, 28 }, VARIANCETYPE::NONE);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 0.0f, 1.0f, 1.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 1.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 1.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 0.0f, 1.0f, 1.0f });
		for (int i = 0; i < 360.0f; i += 10)
		{
			float _angle = i / (PI / 4);
			Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Direction({5.0f * cosf(_angle), 5.0f * sinf(_angle)});
			Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Direction({0, 0});
		}
		return emitter;
	}

	ENTITY CreateParticleEmitter_OTHERSTATIC(cTransform* tar)
	{
		UNREFERENCED_PARAMETER(tar);
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform({ 0.0f, 80.0f }, 0.0f, { 1,1 }));
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0.0f, 0.0f }, 10.0f, 0.1f, 0.2f, 999.0f, 3, 
			0.0f, 0.0f, 2.0f));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 90;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", { 0.0f, 0.0f, 1.0f, 0.5f },
			{ 20,20 }, 2.0f, { 0.0f,0.0f }, { -1.0f, -0.3f }, 100.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 2,1 }, { 28, 20 }, VARIANCETYPE::RANDOM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 0.0f, 0.0f, 1.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 0.0f, 0.0f, 1.0f, 0.1f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 0.0f, 1.0f, 0.9f });
		for (int i = 0; i < 360.0f; i += 10)
		{
			float _angle = i / (PI / 2);
			Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Direction({10.0f * cosf(_angle), 10.0f * sinf(_angle)});
			Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Direction({0, 0});
		}
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Direction({ 0 , 0 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(30.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Velocity(0.0f);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 28, 28 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 20, 20 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 10, 10 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 5, 5 });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Scale({ 1, 1 });
		return emitter;

	}

	ENTITY CreateParticleEmitter_DIVERGENCE(AEVec2 position, float radius, unsigned int count, float lifeTime)
	{
		float rotation = 2.0f * PI / count;
		unsigned int cap = 100 / count;

		for (unsigned int i = 0; i < count; ++i)
		{
			float current = i * rotation;
			AEVec2 curPosition = { position.x + radius * cosf(current),position.y + radius * sinf(current) };
			AEVec2 dirToCenter;
			AEVec2Sub(&dirToCenter, &position, &curPosition);
			float vel = AEVec2Length(&dirToCenter);
			AEVec2Normalize(&dirToCenter, &dirToCenter);

			ENTITY emitter = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(emitter, new cTransform(curPosition, 0.0f, { 1.0f,1.0f }));
			Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0.0f,0.0f }, 10.0f, 2.0f, 3.0f, lifeTime));
			Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = cap;
			Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default", 
				{ 1.0f, 0.0f, 0.0f, 1.0f },
				{ 20.0f,5.0f },
				1.0f, 
				{ 0.0f,0.0f },
				dirToCenter,
				vel,
				atan2f(dirToCenter.y, dirToCenter.x), 
				3);
		}

		return 0;
	}
}

namespace Factory_ParticleFx
{
	ENTITY CreateParticleEmitter_FinaleMisson(AEVec2 position)
	{
		ENTITY emitter = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(emitter, new cTransform(position, 0.0f, { 1.0f,1.0f }));
		Core::Get().AddComponent<cRigidBody>(emitter, new cRigidBody(0, 400.0f, 200.0f, 2.5f));
		Core::Get().GetComponent<cRigidBody>(emitter)->_velocityDirection = { -1.0f, 0 };
		Core::Get().AddComponent<cParticleEmitter>(emitter, new cParticleEmitter({ 0.0f,0.0f }, 5.0f, 0.001f, 0.02f, 0.75f, 3));
		Core::Get().GetComponent<cParticleEmitter>(emitter)->_particleCap = 500;
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignParticleSpawnInfo("Square Mesh", "Particle_Default",
			{ 1.0f, 1.0f, 0.0f, 1.0f }, { 4.0f,4.0f }, 0.6f, { 0.0f,0.0f },
			{ 1.0f, 0.0f }, 100.0f, 0.0f, 0);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 2.0f,2.0f }, { 6.0f, 6.0f }, VARIANCETYPE::RANDOM_UNIFORM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 0.0f, 1.0f, 1.0f, 1.0f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 0.0f, 1.0f, 1.0f, 0.0f });


		return emitter;
	}

}

/******************************************************************************/
/*!
  \brief	Template of various UI Entity to be used in game
			- Main Menu Buttons/Wormholes
			- 
*/
/******************************************************************************/
namespace Factory_UI
{
	ENTITY Create_MM_BeginCampaignUI(AEVec2 position)
	{
		ENTITY begin = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(begin, new cTransform(position, 0, { 160, 40 }));
		//Core::Get().AddComponent<cSprite>(begin, new cSprite(begin, "Square Mesh", "Texture_Default", 0));
		//Core::Get().GetComponent<cSprite>(begin)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(begin, new cUIElement("Start Game"));
		Core::Get().GetComponent<cUIElement>(begin)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(begin)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		//UIEventsManager::Subscribe(begin, &OnButtonClick_MainMenuUI);

		ENTITY wormhole = Factory::CreateWormhole({ position.x,position.y + 50 }, 5.0f, 0.0f, 30.0f, 1);
		Core::Get().AddComponent<cRigidBody>(wormhole, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(wormhole)->_tag = COLLISIONTAG::MENU_BEGIN;
		Core::Get().AddComponent<cCollision>(wormhole, new cCollision);

		return begin;
	}
	ENTITY Create_MM_OptionsUI(AEVec2 position)
	{
		ENTITY options = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(options, new cTransform(position, 0, { 160, 40 }));
		//Core::Get().AddComponent<cSprite>(options, new cSprite(options, "Square Mesh", "Texture_Default", 0));
		//Core::Get().GetComponent<cSprite>(options)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(options, new cUIElement("Options"));
		Core::Get().GetComponent<cUIElement>(options)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(options)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };

		ENTITY wormhole = Factory::CreateWormhole({ position.x,position.y + 50 }, 5.0f, 0.0f, 30.0f, 2);
		Core::Get().AddComponent<cRigidBody>(wormhole, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(wormhole)->_tag = COLLISIONTAG::MENU_OPTIONS;
		Core::Get().AddComponent<cCollision>(wormhole, new cCollision);
		return 0;

	}
	ENTITY Create_MM_CreditsUI(AEVec2 position)
	{
		ENTITY credits = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits, new cTransform(position, 0, { 160, 40 }));
		//Core::Get().AddComponent<cSprite>(credits, new cSprite(credits, "Square Mesh", "Texture_Default", 0));
		//Core::Get().GetComponent<cSprite>(credits)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(credits, new cUIElement("Credits"));
		Core::Get().GetComponent<cUIElement>(credits)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(credits)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		//UIEventsManager::Subscribe(credits, &OnButtonClick_MainMenuUI);

		ENTITY wormhole = Factory::CreateWormhole({ position.x, position.y +50 }, 5.0f, 0.0f, 30.0f, 3);
		Core::Get().AddComponent<cRigidBody>(wormhole, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(wormhole)->_tag = COLLISIONTAG::MENU_CREDITS;
		Core::Get().AddComponent<cCollision>(wormhole, new cCollision);
		return 0;
	}
	ENTITY Create_MM_Quit(AEVec2 position)
	{
		ENTITY quit = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(quit, new cTransform(position, 0, { 160, 40 }));
		//Core::Get().AddComponent<cSprite>(quit, new cSprite(quit, "Square Mesh", "Texture_Default", 0));
		//Core::Get().GetComponent<cSprite>(quit)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(quit, new cUIElement("Quit"));
		Core::Get().GetComponent<cUIElement>(quit)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(quit)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };

		ENTITY wormhole = Factory::CreateWormhole({ position.x,position.y + 50 }, 5.0f, 0.0f, 30.0f, 4);
		Core::Get().AddComponent<cRigidBody>(wormhole, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(wormhole)->_tag = COLLISIONTAG::MENU_QUIT;
		Core::Get().AddComponent<cCollision>(wormhole, new cCollision);

		return 0;
	}

	ENTITY Create_MM_BackToMain(AEVec2 position)
	{
		ENTITY back = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(back, new cTransform(position, 0, { 160, 40 }));
		Core::Get().AddComponent<cUIElement>(back, new cUIElement("Back To Main Menu"));
		Core::Get().GetComponent<cUIElement>(back)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(back)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };

		ENTITY wormhole = Factory::CreateWormhole({ position.x,position.y + 50 }, 5.0f, 0.0f, 30.0f, 4);
		Core::Get().AddComponent<cRigidBody>(wormhole, new cRigidBody(100.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(wormhole)->_tag = COLLISIONTAG::MENU_BACK;
		Core::Get().AddComponent<cCollision>(wormhole, new cCollision);
		return 0;
	}


	// "End Of Space" Game Logo
	ENTITY Create_GameLogo(AEVec2 position, AEVec2 scale)
	{
		ENTITY gameLogo = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(gameLogo, new cTransform(position, 0, scale));
		Core::Get().AddComponent<cSprite>(gameLogo, new cSprite(gameLogo, "Square Mesh", "GameLogo", 0));
		return gameLogo;
	}

	//This includes health bar, shield bar and thruster fuel
	void Create_PlayerUserInterface(unsigned int health, unsigned int shield)
	{
		AEVec2 spritePos;
		// Default 3 Health for Player 
		for (unsigned int i = 0; i < health; ++i)
		{
			spritePos = ScreenBasedCoords(100.0f + 50.0f * i, 75.0f, UI_ANCHOR::BOTTOMLEFT);
			Create_SingleHealthBar(spritePos, i);
		}

		// Default 3 Shield for Player
		for (unsigned int i = 0; i < shield; ++i)
		{
			spritePos = ScreenBasedCoords(250.0f + 50.0f * i, 75.0f, UI_ANCHOR::BOTTOMLEFT);
			Create_SingleShieldBar(spritePos, i);
		}

		// Thruster speed interface
		spritePos = ScreenBasedCoords(-150.0f, -75.0f, UI_ANCHOR::TOPRIGHT);
		Create_ThrusterUI(spritePos);

		// Objectives UI
		CreateUI_Objective_Base();
	}

	void CreateLowHealthInterface()
	{
		AEVec2 spritePos;
		spritePos = ScreenBasedCoords(0.0f, 230.0f, UI_ANCHOR::CENTER);
		Create_LowHealthUI(spritePos);
	}

	void CreateShieldsDownInterface()
	{
		AEVec2 spritePos;
		spritePos = ScreenBasedCoords(0.0f, 230.0f, UI_ANCHOR::CENTER);
		Create_ShieldsDownUI(spritePos);
	}

	void CreateBossIncomingInterface()
	{
		AEVec2 spritePos;
		spritePos = ScreenBasedCoords(0.0f, 230.0f, UI_ANCHOR::CENTER);
		Create_BossIncomingUI(spritePos);
	}

	ENTITY Create_SingleHealthBar(AEVec2 position, int i)
	{
		ENTITY hpBar = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(hpBar, new cTransform(position, 0, { 50, 50 }));
		Core::Get().AddComponent<cSprite>(hpBar, new cSprite(hpBar, "UI_HP bar", "HP_FILL", 0));
		Core::Get().GetComponent<cSprite>(hpBar)->_colorTint = { 1.0f,0, 0.2f,0.8f };
		Core::Get().AddComponent<cUIElement>(hpBar, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::HEALTH, i));
		UIEventsManager::Subscribe(hpBar, &OnHealthChange_HPUI);

		return hpBar;
	}

	ENTITY Create_SingleShieldBar(AEVec2 position, int i)
	{
		ENTITY shieldBar = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(shieldBar, new cTransform(position, 0, { 50, 50 }));
		Core::Get().AddComponent<cSprite>(shieldBar, new cSprite(shieldBar, "UI_HP bar", "HP_FILL", 0));
		Core::Get().GetComponent<cSprite>(shieldBar)->_colorTint = { 0.0f,0.0f, 1.0f,0.8f };
		Core::Get().AddComponent<cUIElement>(shieldBar, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::SHIELD, i));
		UIEventsManager::Subscribe(shieldBar, &OnShieldChange_ShieldUI);

		return shieldBar;
	}

	ENTITY Create_ShieldBubble()
	{
		ENTITY shieldBubble = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(shieldBubble, new cTransform({ 0,0 }, 0, { 100, 100 }));
		Core::Get().AddComponent<cSprite>(shieldBubble, new cSprite(shieldBubble, "Square Mesh", "Player_Shield", 2));
		Core::Get().GetComponent<cSprite>(shieldBubble)->_colorTint = { 1.0f,1.0f, 1.0f, 0.0f };			//invisible
		Core::Get().AddComponent<cUIElement>(shieldBubble, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::SHIELDBUBBLE));
		Core::Get().GetComponent<cUIElement>(shieldBubble)->_isActive = false;			//invisible
		UIEventsManager::Subscribe(shieldBubble, &OnShieldActivate_ShieldBubble);

		return shieldBubble;
	}

	ENTITY Create_ThrusterUI(AEVec2 position)
	{
		ENTITY thruster = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(thruster, new cTransform(position, 0, { 50, 50 }));			//mesh scale of 50
		Core::Get().AddComponent<cSprite>(thruster, new cSprite(thruster, "UI_Thruster", "Texture_Fill3", 0));
		Core::Get().GetComponent<cSprite>(thruster)->_colorTint = { 1.0f,1.0f, 0.0f,0.8f };
		Core::Get().AddComponent<cUIElement>(thruster, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::THRUSTER));
		UIEventsManager::Subscribe(thruster, &OnThrusterChange_ThrusterUI);

		return thruster;
	}

	ENTITY Create_LowHealthUI(AEVec2 position)
	{
		ENTITY lowHealth = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(lowHealth, new cTransform(position, 0, { 350, 50 }));
		Core::Get().AddComponent<cSprite>(lowHealth, new cSprite(lowHealth, "Square Mesh", "Low_Health", 0));
		Core::Get().GetComponent<cSprite>(lowHealth)->_colorTint = { 1.0f,1.0f, 1.0f, 0.0f };			//invisible
		Core::Get().AddComponent<cUIElement>(lowHealth, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::LOW_HEALTH_UI));
		Core::Get().GetComponent<cUIElement>(lowHealth)->_isActive = false;			//invisible

		Core::Get().AddComponent<cTimeline>(lowHealth, new cTimeline(g_appTime, g_appTime + 1.8f, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(lowHealth)->_colorTint.r, Core::Get().GetComponent<cTimeline>(lowHealth));
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(lowHealth)->_colorTint.a, Core::Get().GetComponent<cTimeline>(lowHealth), 0.00f, 0.0f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(lowHealth)->_colorTint.a, Core::Get().GetComponent<cTimeline>(lowHealth), 0.5f, 1.5f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(lowHealth)->_colorTint.a, Core::Get().GetComponent<cTimeline>(lowHealth), 1.5f, 0.5f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(lowHealth)->_colorTint.a, Core::Get().GetComponent<cTimeline>(lowHealth), 1.8f, 0.0f);
		UIEventsManager::Subscribe(lowHealth, &OnLowHealth_HPIndicator); //Appear When low health

		return lowHealth;

	}

	ENTITY Create_ShieldsDownUI(AEVec2 position)
	{
		ENTITY shieldDown = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(shieldDown, new cTransform(position, 0, { 380, 50 }));
		Core::Get().AddComponent<cSprite>(shieldDown, new cSprite(shieldDown, "Square Mesh", "Shield_Down", 0));
		Core::Get().GetComponent<cSprite>(shieldDown)->_colorTint = { 1.0f,1.0f, 1.0f, 0.0f };			//invisible
		Core::Get().AddComponent<cUIElement>(shieldDown, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::SHIELD_DOWN_UI));
		Core::Get().GetComponent<cUIElement>(shieldDown)->_isActive = false;			//invisible

		Core::Get().AddComponent<cTimeline>(shieldDown, new cTimeline(g_appTime, g_appTime + 1.8f, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(shieldDown)->_colorTint.a, Core::Get().GetComponent<cTimeline>(shieldDown));
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(shieldDown)->_colorTint.a, Core::Get().GetComponent<cTimeline>(shieldDown), 0.0f, 0.0f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(shieldDown)->_colorTint.a, Core::Get().GetComponent<cTimeline>(shieldDown), 0.5f, 1.5f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(shieldDown)->_colorTint.a, Core::Get().GetComponent<cTimeline>(shieldDown), 1.5f, 0.5f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(shieldDown)->_colorTint.a, Core::Get().GetComponent<cTimeline>(shieldDown), 1.80f, 0.0f);
		UIEventsManager::Subscribe(shieldDown, &OnShieldDown_ShieldIndicator); //Appear When shield

		return shieldDown;
	}

	ENTITY Create_BossIncomingUI(AEVec2 position)
	{
		ENTITY boss = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(boss, new cTransform(position, 0, { 380, 50 }));
		Core::Get().AddComponent<cSprite>(boss, new cSprite(boss, "Square Mesh", "Boss_Incoming", 0));
		Core::Get().GetComponent<cSprite>(boss)->_colorTint = { 1.0f,1.0f, 1.0f, 0.0f };			//invisible
		Core::Get().AddComponent<cUIElement>(boss, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::BOSS_INCOMING_UI));
		Core::Get().GetComponent<cUIElement>(boss)->_isActive = false;			//invisible

		Core::Get().AddComponent<cTimeline>(boss, new cTimeline(g_appTime, g_appTime + 1.8f, true));
		AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(boss)->_colorTint.a, Core::Get().GetComponent<cTimeline>(boss));
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(boss)->_colorTint.a, Core::Get().GetComponent<cTimeline>(boss), 0.0f, 0.0f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(boss)->_colorTint.a, Core::Get().GetComponent<cTimeline>(boss), 0.5f, 1.5f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(boss)->_colorTint.a, Core::Get().GetComponent<cTimeline>(boss), 1.5f, 0.5f);
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(boss)->_colorTint.a, Core::Get().GetComponent<cTimeline>(boss), 1.80f, 0.0f);
		UIEventsManager::Subscribe(boss, &OnBossIncoming_EnemyIndicator); //Appear When boss comes

		return boss;
	}

	void Create_ChooseThree(AEVec2 centralPos, unsigned int reroll)
	{
		ENTITY border = 0, fakeupgrade = 0;
		float borderSize = 100, borderSpace = 100;
		AEVec2 startingPos;

		// Title of Upgrade
		AEVec2Set(&startingPos, centralPos.x, centralPos.y + 100);
		ENTITY text = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(text, new cTransform(startingPos, 0, { 1, 1 }));
		Core::Get().AddComponent<cUIElement>(text, new cUIElement("Choose Your Upgrade"));
		Core::Get().GetComponent<cUIElement>(text)->_role = UI_ROLE::C3_TEXT;
		Core::Get().GetComponent<cUIElement>(text)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(text)->_text._usingScreenSpace = true;

		// Number of Rerolls Title
		AEVec2Set(&startingPos, centralPos.x, centralPos.y + 75);
		text = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(text, new cTransform(startingPos, 0, { 1, 1 }));
		Core::Get().AddComponent<cUIElement>(text, new cUIElement("Remaining Rerolls: "));
		Core::Get().GetComponent<cUIElement>(text)->_role = UI_ROLE::C3_TEXT;
		Core::Get().GetComponent<cUIElement>(text)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(text)->_text._usingScreenSpace = true;

		// Number of Rerolls
		AEVec2Set(&startingPos, centralPos.x + 120, centralPos.y + 75);
		text = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(text, new cTransform(startingPos, 0, { 1, 1 }));
		char buffer[4];
		_itoa_s(reroll, buffer, 10);
		Core::Get().AddComponent<cUIElement>(text, new cUIElement(buffer));
		Core::Get().GetComponent<cUIElement>(text)->_role = UI_ROLE::C3_TEXT;
		Core::Get().GetComponent<cUIElement>(text)->_roleIndex = 1;
		Core::Get().GetComponent<cUIElement>(text)->_roleIndex2 = reroll;		//Used to track reroll count
		Core::Get().GetComponent<cUIElement>(text)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(text)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(text, &UpdateRerollCount);

		// Three Roulette
		AEVec2Set(&centralPos, centralPos.x - borderSize - borderSpace, centralPos.y);
		for (int i = 0; i < 3; ++i)
		{
			AEVec2Set(&startingPos, centralPos.x + (borderSize + borderSpace) * i, centralPos.y);
			border = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(border, new cTransform(startingPos, 0.0f, { borderSize , borderSize }));
			Core::Get().AddComponent<cSprite>(border, new cSprite(border, "Square Mesh", "Texture_Default", 0));
			Core::Get().GetComponent<cSprite>(border)->_colorTint = { 1.0f, 0.0f, 0.0f, 1.0f };
			Core::Get().AddComponent<cUIElement>(border, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_FRAME));

			AEVec2Set(&startingPos, startingPos.x, centralPos.y);
			fakeupgrade = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(fakeupgrade, new cTransform(startingPos, 0.0f, { borderSize * 0.9f, borderSize * 0.9f }));
			Core::Get().AddComponent<cSprite>(fakeupgrade, new cSprite(fakeupgrade, "Square Mesh2", "Random_Upgrade", 0));
			Core::Get().GetComponent<cSprite>(fakeupgrade)->_colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
			Core::Get().AddComponent<cUIElement>(fakeupgrade, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_FAKEUPGRADE, 2 + i));

			Core::Get().AddComponent<cTimeline>(fakeupgrade, new cTimeline(g_appTime, g_appTime + 0.5f + (i * 0.5f), false));
			AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(fakeupgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(fakeupgrade));
			AddNewNode_Float(&Core::Get().GetComponent<cSprite>(fakeupgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(fakeupgrade), 0.45f + (i * 0.5f), -1.5f * (i + 2));
			AddNewTimeline_Void(Create_ChoosableUpgrade, Core::Get().GetComponent<cTimeline>(fakeupgrade));
			AddNewNode_Void(Create_ChoosableUpgrade, Core::Get().GetComponent<cTimeline>(fakeupgrade), 0.49f + (i * 0.5f), fakeupgrade);
		
			// Item Description
			AEVec2Set(&startingPos, startingPos.x, centralPos.y - 100.0f);
			text = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(text, new cTransform(startingPos, 0, { 1, 1 }));
			Core::Get().AddComponent<cUIElement>(text, new cUIElement("NOT Ready"));
			Core::Get().GetComponent<cUIElement>(text)->_role = UI_ROLE::C3_TEXT;
			Core::Get().GetComponent<cUIElement>(text)->_roleIndex = 2 + i;
			Core::Get().GetComponent<cUIElement>(text)->_text._anchor = TEXT_ANCHOR::CENTER;
			Core::Get().GetComponent<cUIElement>(text)->_text._usingScreenSpace = true;
			UIEventsManager::Subscribe(text, &UpdateDescriptionText);
		}
	}

	void Create_ChoosableUpgrade(ENTITY entity)
	{
		AEVec2 position = Core::Get().GetComponent<cTransform>(entity)->_position;
		unsigned int slot = Core::Get().GetComponent<cUIElement>(entity)->_roleIndex;

		ENTITY realUpgrade = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(realUpgrade, new cTransform(position, 0.0f, { 100 * 0.9f, 100 * 0.9f }));
		Core::Get().AddComponent<cUIElement>(realUpgrade, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_UPGRADE));
		Core::Get().GetComponent<cUIElement>(realUpgrade)->_roleIndex = UpgradeManager::RandomUpgrade();
		unsigned int upgradeIndex = Core::Get().GetComponent<cUIElement>(realUpgrade)->_roleIndex;
		UIEventsManager::Broadcast(new Events::OnUpgradeDescpChange(static_cast<int>(upgradeIndex), slot));

		//Different sprite based on upgrade assigned
		Core::Get().AddComponent<cSprite>(realUpgrade, new cSprite(realUpgrade, "Square Mesh2", UpgradeManager::GetUpgradeImage(upgradeIndex), 0));
		Core::Get().GetComponent<cSprite>(realUpgrade)->_colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };

		//Continue spinning
		Core::Get().AddComponent<cTimeline>(realUpgrade, new cTimeline(g_appTime, g_appTime + 0.5f, false));
		AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(realUpgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(realUpgrade));
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(realUpgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(realUpgrade), 0.45f, -0.5f);
		UIEventsManager::Subscribe(realUpgrade, &OnButtonClick_Upgrades);
		UIEventsManager::Subscribe(realUpgrade, &OnButtonHover_Upgrades);
	}

	ENTITY Create_AIIndicator(ENTITY ai, AEVec2 aiDir, int indicatorType)
	{
		AEVec2 aiPos = Core::Get().GetComponent<cTransform>(ai)->_position;
		float screenGradiant = g_WorldMaxY / g_WorldMaxX;
		AEVec2 aiDir_Normalise;
		AEVec2Normalize(&aiDir_Normalise, &aiDir);

		if (aiDir.x < FLT_EPSILON && aiDir.x > -FLT_EPSILON) //Horizontal axis
		{
			aiDir.x = aiDir_Normalise.x * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
			aiDir.y = aiDir_Normalise.y * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
		}
		else if (aiDir.y < FLT_EPSILON && aiDir.y > -FLT_EPSILON) //Vertical axis
		{
			aiDir.x = aiDir_Normalise.x * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
			aiDir.y = aiDir_Normalise.y * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
		}
		else
		{
			float aiGradiant = aiDir.y / aiDir.x;
			if (fabs(aiGradiant) < screenGradiant)		//Vertical Axis
			{
				aiDir.x = aiDir_Normalise.x * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
				aiDir.y = aiDir_Normalise.y * (g_WorldMaxX / fabs(aiDir_Normalise.x)) * 0.9f;
			}
			else if (fabs(aiGradiant) > screenGradiant)	//Horizontal Axis
			{
				aiDir.x = aiDir_Normalise.x * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
				aiDir.y = aiDir_Normalise.y * (g_WorldMaxY / fabs(aiDir_Normalise.y)) * 0.9f;
			}
		}
		//Calculate angle
		float angle = atan2f(aiDir.y, aiDir.x);

		//Arrow Image
		ENTITY aiUI = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(aiUI, new cTransform(aiDir, angle, { 40.0,30.0 }));
		Core::Get().AddComponent<cSprite>(aiUI, new cSprite(aiUI, "Square Mesh", "AI_Indicator", 0));
		if (indicatorType == 0 || indicatorType == 1)
		{
		}
		else if (indicatorType == 3)
		{
			Core::Get().GetComponent<cSprite>(aiUI)->_colorTint = { 1.0f, 0.0f, 0.0f, 1.0f };
		}
		else if (indicatorType == 5)
		{
			Core::Get().GetComponent<cSprite>(aiUI)->_colorTint = { 0.0f, 1.0f, 0.0f, 1.0f };
		}
		Core::Get().AddComponent<cUIElement>(aiUI, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::INDICATE_AI, ai));
		Core::Get().GetComponent<cUIElement>(aiUI)->_roleIndex2 = 1;

		//Type of indicator image
		AEVec2Scale(&aiDir, &aiDir, 0.95f);
		ENTITY aiUI2 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(aiUI2, new cTransform(aiDir, 0.0f, { 30.0,30.0 }));
		if (indicatorType == 3)	//Boss Icon
		{
			Core::Get().AddComponent<cSprite>(aiUI2, new cSprite(aiUI2, "Square Mesh", "Skull_Boss", 0));
		}
		else if(indicatorType == 0 || indicatorType == 1)  //Normal Enemy
		{
			Core::Get().AddComponent<cSprite>(aiUI2, new cSprite(aiUI2, "Square Mesh", "Skull_Normal", 0));
		}
		else if(indicatorType == 5)   //Objectives
		{
			Core::Get().GetComponent<cTransform>(aiUI2)->_scale.x = 15;
			Core::Get().GetComponent<cTransform>(aiUI2)->_scale.y = 50;
			Core::Get().AddComponent<cSprite>(aiUI2, new cSprite(aiUI2, "Square Mesh", "Objective_Symbol", 0));
		}
		Core::Get().AddComponent<cUIElement>(aiUI2, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::INDICATE_AI, ai));
		Core::Get().GetComponent<cUIElement>(aiUI2)->_roleIndex2 = 2;

		return aiUI;
	}
	ENTITY CreateUI_Objective_Base()
	{
		AEVec2 textPos = ScreenBasedCoords(0.025f, -0.05f, UI_ANCHOR::TOPLEFT, true);

		ENTITY objectiveTitle = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(objectiveTitle, new cTransform(textPos, 0, { 1,1 }));
		Core::Get().AddComponent<cUIElement>(objectiveTitle, new cUIElement("Objectives"));
		Core::Get().GetComponent<cUIElement>(objectiveTitle)->_role = UI_ROLE::OBJECTIVES;
		Core::Get().GetComponent<cUIElement>(objectiveTitle)->_roleIndex = 0;
		Core::Get().GetComponent<cUIElement>(objectiveTitle)->_text._usingScreenSpace = true;

		return objectiveTitle;
	}

	ENTITY CreateUI_AddObjective(unsigned int index, const char* text)
	{
		AEVec2 textPos = ScreenBasedCoords(0.025f, -0.05f - (0.04f * index), UI_ANCHOR::TOPLEFT, true);

		ENTITY objective = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(objective, new cTransform(textPos, 0, { 1,1 }));
		Core::Get().AddComponent<cUIElement>(objective, new cUIElement(text));
		Core::Get().GetComponent<cUIElement>(objective)->_role = UI_ROLE::OBJECTIVES;
		Core::Get().GetComponent<cUIElement>(objective)->_roleIndex = index;
		Core::Get().GetComponent<cUIElement>(objective)->_text._usingScreenSpace = true;

		textPos = ScreenBasedCoords(0.015f, -0.05f - (0.04f * index), UI_ANCHOR::TOPLEFT, true);
		ENTITY tickbox = CreateUI_TickBox(textPos.x, textPos.y, 20, 0);
		return tickbox;
	}

	ENTITY CreateUI_AddObjective_Finale(unsigned int index, const char* text)
	{
		AEVec2 textPos = ScreenBasedCoords(0.025f, -0.05f - (0.04f * index), UI_ANCHOR::TOPLEFT, true);

		ENTITY objective = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(objective, new cTransform(textPos, 0, { 1,1 }));
		Core::Get().AddComponent<cUIElement>(objective, new cUIElement(text));
		Core::Get().GetComponent<cUIElement>(objective)->_role = UI_ROLE::OBJECTIVES;
		Core::Get().GetComponent<cUIElement>(objective)->_roleIndex = index;
		Core::Get().GetComponent<cUIElement>(objective)->_text._usingScreenSpace = true;
		Core::Get().GetComponent<cUIElement>(objective)->_text._colorTint = { 1.0f, 1.0f, 0.0f, 1.0f };

		textPos = ScreenBasedCoords(0.016f, -0.05f - (0.04f * index), UI_ANCHOR::TOPLEFT, true);
		ENTITY tickbox = CreateUI_TickBox(textPos.x, textPos.y, 20, 0);
		Core::Get().GetComponent<cSprite>(tickbox)->_colorTint = { 1.0f, 1.0f, 0.0f, 1.0f };

		textPos = ScreenBasedCoords(0.14f, -0.05f - (0.04f * index) - 0.02f, UI_ANCHOR::TOPLEFT, true);
		Factory_ParticleFx::CreateParticleEmitter_FinaleMisson(textPos);
		return tickbox;
	}


	void CreateUI_GameWin()
	{
		ENTITY panel = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(panel, new cTransform({ 0,0 }, 0, { 730,400 }));
		Core::Get().AddComponent<cSprite>(panel, new cSprite(panel, "Square Mesh", "GameWin_Menu", 0));
		Core::Get().AddComponent<cUIElement>(panel, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::GAMEWIN, 0));
		UIEventsManager::Subscribe(panel, &ToggleGameWinWindow);

		ENTITY exit = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(exit, new cTransform({ 0, -100 }, 0, { 218, 40 }));
		Core::Get().AddComponent<cSprite>(exit, new cSprite(exit, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(exit)->_colorTint = { 0.0f, 0.55f, 1.0f, 0.0f };
		Core::Get().AddComponent<cUIElement>(exit, new cUIElement("Exit to Main Menu"));
		Core::Get().GetComponent<cUIElement>(exit)->_role = UI_ROLE::GAMEWIN;
		Core::Get().GetComponent<cUIElement>(exit)->_roleIndex = 2;		//Toggle Transparency
		Core::Get().GetComponent<cUIElement>(exit)->_roleIndex2 = 2;	//Exit to main menu
		Core::Get().GetComponent<cUIElement>(exit)->_text._anchor = TEXT_ANCHOR::CENTERLEFT;
		Core::Get().GetComponent<cUIElement>(exit)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().GetComponent<cUIElement>(exit)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(exit, &ToggleGameOverWindow);
		UIEventsManager::Subscribe(exit, &OnButtonClick_GameWinMenuUI);


	}

	void CreateUI_GameOver()
	{
		ENTITY panel = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(panel, new cTransform({ 0,0 }, 0, { 730,400 }));
		Core::Get().AddComponent<cSprite>(panel, new cSprite(panel, "Square Mesh", "GameOver_Menu", 0));
		Core::Get().AddComponent<cUIElement>(panel, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::GAMEOVER, 0));
		UIEventsManager::Subscribe(panel, &ToggleGameOverWindow);

		ENTITY restart = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(restart, new cTransform({ -150, -100 }, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(restart, new cSprite(restart, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(restart)->_colorTint = { 0.0f, 0.55f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(restart, new cUIElement("Restart"));
		Core::Get().GetComponent<cUIElement>(restart)->_role = UI_ROLE::GAMEOVER;
		Core::Get().GetComponent<cUIElement>(restart)->_roleIndex = 2;
		Core::Get().GetComponent<cUIElement>(restart)->_roleIndex2 = 1;		//Restart Game
		Core::Get().GetComponent<cUIElement>(restart)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(restart)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		Core::Get().GetComponent<cUIElement>(restart)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(restart, &ToggleGameOverWindow);
		UIEventsManager::Subscribe(restart, &OnButtonClick_GameOverMenuUI);

		ENTITY exit = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(exit, new cTransform({ 150, -100 }, 0, { 218, 40 }));
		Core::Get().AddComponent<cSprite>(exit, new cSprite(exit, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(exit)->_colorTint = { 0.0f, 0.55f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(exit, new cUIElement("Exit to Main Menu"));
		Core::Get().GetComponent<cUIElement>(exit)->_role = UI_ROLE::GAMEOVER;
		Core::Get().GetComponent<cUIElement>(exit)->_roleIndex = 2;		//Toggle Transparency
		Core::Get().GetComponent<cUIElement>(exit)->_roleIndex2 = 2;	//Exit to main menu
		Core::Get().GetComponent<cUIElement>(exit)->_text._anchor = TEXT_ANCHOR::CENTERLEFT;
		Core::Get().GetComponent<cUIElement>(exit)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		Core::Get().GetComponent<cUIElement>(exit)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(exit, &ToggleGameOverWindow);
		UIEventsManager::Subscribe(exit, &OnButtonClick_GameOverMenuUI);


	}

	void CreateUI_Pause()
	{
		ENTITY panel = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(panel, new cTransform({ 0,0 }, 0, { 730,400 }));
		Core::Get().AddComponent<cSprite>(panel, new cSprite(panel, "Square Mesh", "Pause_Menu", 0));
		Core::Get().GetComponent<cSprite>(panel)->_colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().AddComponent<cUIElement>(panel, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::PAUSE, 0));
		UIEventsManager::Subscribe(panel, &TogglePauseWindow);

		ENTITY settings = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(settings, new cTransform({ 300, 150 }, 0, { 40,40 }));
		Core::Get().AddComponent<cSprite>(settings, new cSprite(panel, "Square Mesh", "Settings_Icon", 0));
		Core::Get().GetComponent<cSprite>(settings)->_colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().AddComponent<cUIElement>(settings, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::PAUSE, 0));
		Core::Get().GetComponent<cUIElement>(settings)->_roleIndex = 0;		//Toggle Text Transparency
		Core::Get().GetComponent<cUIElement>(settings)->_roleIndex2 = 4;	//Settings page Game
		UIEventsManager::Subscribe(settings, &TogglePauseWindow);
		UIEventsManager::Subscribe(settings, &OnButtonClick_PauseMenuUI);

		ENTITY resume = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(resume, new cTransform({-230, -100}, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(resume, new cSprite(resume, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(resume)->_colorTint = { 0.0f, 0.55f, 1.0f, 0.0f };
		Core::Get().AddComponent<cUIElement>(resume, new cUIElement("Resume"));
		Core::Get().GetComponent<cUIElement>(resume)->_role = UI_ROLE::PAUSE;
		Core::Get().GetComponent<cUIElement>(resume)->_roleIndex = 2;	//Toggle Text Transparency
		Core::Get().GetComponent<cUIElement>(resume)->_roleIndex2 = 1;	//Resume Game

		Core::Get().GetComponent<cUIElement>(resume)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(resume)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().GetComponent<cUIElement>(resume)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(resume, &TogglePauseWindow);
		UIEventsManager::Subscribe(resume, &OnButtonClick_PauseMenuUI);

		ENTITY restart = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(restart, new cTransform({ 0, -100 }, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(restart, new cSprite(restart, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(restart)->_colorTint = { 0.0f, 0.55f, 1.0f, 0.0f };
		Core::Get().AddComponent<cUIElement>(restart, new cUIElement("Restart"));
		Core::Get().GetComponent<cUIElement>(restart)->_role = UI_ROLE::PAUSE;
		Core::Get().GetComponent<cUIElement>(restart)->_roleIndex = 2;
		Core::Get().GetComponent<cUIElement>(restart)->_roleIndex2 = 2;		//Restart Game
		Core::Get().GetComponent<cUIElement>(restart)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(restart)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().GetComponent<cUIElement>(restart)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(restart, &TogglePauseWindow);
		UIEventsManager::Subscribe(restart, &OnButtonClick_PauseMenuUI);

		ENTITY exit = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(exit, new cTransform({ 230, -100 }, 0, { 218, 40 }));
		Core::Get().AddComponent<cSprite>(exit, new cSprite(exit, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(exit)->_colorTint = { 0.0f, 0.55f, 1.0f, 0.0f };
		Core::Get().AddComponent<cUIElement>(exit, new cUIElement("Exit to Main Menu"));
		Core::Get().GetComponent<cUIElement>(exit)->_role = UI_ROLE::PAUSE;
		Core::Get().GetComponent<cUIElement>(exit)->_roleIndex = 2;		//Toggle Transparency
		Core::Get().GetComponent<cUIElement>(exit)->_roleIndex2 = 3;	//Exit to main menu
		Core::Get().GetComponent<cUIElement>(exit)->_text._anchor = TEXT_ANCHOR::CENTERLEFT;
		Core::Get().GetComponent<cUIElement>(exit)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().GetComponent<cUIElement>(exit)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(exit, &TogglePauseWindow);
		UIEventsManager::Subscribe(exit, &OnButtonClick_PauseMenuUI);
	}

	void  CreateUI_ExitConfirmation()
	{
		ENTITY panel = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(panel, new cTransform({ 0,0 }, 0, { 500,300 }));
		Core::Get().AddComponent<cSprite>(panel, new cSprite(panel, "Square Mesh", "Pause_Confirmation", 0));
		Core::Get().GetComponent<cSprite>(panel)->_colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(panel, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::QUIT, 0));
		UIEventsManager::Subscribe(panel, &ToggleConfirmationWindow);

		ENTITY yes = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(yes, new cTransform({ -100, -100 }, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(yes, new cSprite(yes, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(yes)->_colorTint = { 0.0f, 0.55f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(yes, new cUIElement("YES"));
		Core::Get().GetComponent<cUIElement>(yes)->_role = UI_ROLE::QUIT;
		Core::Get().GetComponent<cUIElement>(yes)->_roleIndex = 2;	//Toggle Text Transparency
		Core::Get().GetComponent<cUIElement>(yes)->_roleIndex2 = 1;	//Exit Game
											 
		Core::Get().GetComponent<cUIElement>(yes)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(yes)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		Core::Get().GetComponent<cUIElement>(yes)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(yes, &ToggleConfirmationWindow);
		UIEventsManager::Subscribe(yes, &OnButtonClick_ConfirmationMenuUI);

		ENTITY no = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(no, new cTransform({ 100, -100 }, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(no, new cSprite(no, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(no)->_colorTint = { 0.0f, 0.55f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(no, new cUIElement("NO"));
		Core::Get().GetComponent<cUIElement>(no)->_role = UI_ROLE::QUIT;
		Core::Get().GetComponent<cUIElement>(no)->_roleIndex = 2;
		Core::Get().GetComponent<cUIElement>(no)->_roleIndex2 = 2;		//Resume Game
		Core::Get().GetComponent<cUIElement>(no)->_text._anchor = TEXT_ANCHOR::CENTER;
		Core::Get().GetComponent<cUIElement>(no)->_text._colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		Core::Get().GetComponent<cUIElement>(no)->_text._usingScreenSpace = true;
		UIEventsManager::Subscribe(no, &ToggleConfirmationWindow);
		UIEventsManager::Subscribe(no, &OnButtonClick_ConfirmationMenuUI);
	}

	void Create_InGameOptions()
	{
		ENTITY panel = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(panel, new cTransform({ 0,0 }, 0, { 500,300 }));
		Core::Get().AddComponent<cSprite>(panel, new cSprite(panel, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(panel)->_colorTint = { 1.0f, 0.4f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(panel, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::INGAMEOPTIONS, 0));

		ENTITY soundTB = CreateUI_Option_TickBox_Sound(-100, 30, 40.0f, 0);
		Core::Get().GetComponent<cSprite>(soundTB)->_colorTint.a = 1.0f;
		Factory_UI::CreateUI_Text(0, 30, "Mute All Audio");
		ENTITY optionTB = CreateUI_Option_TickBox_Fullscreen(-100, -30, 40.0f, 0);
		Core::Get().GetComponent<cSprite>(optionTB)->_colorTint.a = 1.0f;
		Factory_UI::CreateUI_Text(0, -30, "Windowed Mode");
		Core::Get().GetComponent<cSprite>(Core::Get().GetComponent<cUIElement>(soundTB)->_roleIndex)->_colorTint.a = g_isMute ? 1.0f : 0.0f;
		Core::Get().GetComponent<cSprite>(Core::Get().GetComponent<cUIElement>(optionTB)->_roleIndex)->_colorTint.a = !g_isFullScreen ? 1.0f : 0.0f;

		Core::Get().GetComponent<cUIElement>(soundTB)->_roleIndex;
		Core::Get().GetComponent<cUIElement>(optionTB)->_roleIndex;
	}

	ENTITY CreateUI_Text(float posX, float posY, const char* text)
	{
		AEVec2 newPostion;
		AEVec2Set(&newPostion, posX, posY);

		ENTITY uiEntity = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(uiEntity, new cTransform(newPostion, 0, { 1,1 }));
		Core::Get().AddComponent<cUIElement>(uiEntity, new cUIElement(text));
		return uiEntity;
	}

	ENTITY CreateUI_FloatingDamage(ENTITY target, int startHealth, int damageValue)
	{
		ENTITY uiEntity = Core::Get().CreateEntity();

		cTransform* transform = Core::Get().GetComponent<cTransform>(target);
		Core::Get().AddComponent<cTransform>(uiEntity, new cTransform(transform->_position, 0, { 1,1 }));
		Core::Get().AddComponent<cUIElement>(uiEntity, new cUIElement(UI_TYPE::TEXT, UI_ROLE::DAMAGE_FLOAT, target));
		Core::Get().GetComponent<cUIElement>(uiEntity)->_roleIndex2 = startHealth - damageValue;
		Core::Get().GetComponent<cUIElement>(uiEntity)->_text._colorTint = { 1.0f,1.0f,1.0f,1.0f };
		EditText(uiEntity, "", startHealth);
		return uiEntity;
	}

	ENTITY CreateUI_TickBox(float posX, float posY, float size, unsigned int layer)
	{
		ENTITY tick = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(tick, new cTransform({ posX,posY }, 0, { size * 0.5f,size * 0.5f }));
		Core::Get().AddComponent<cSprite>(tick, new cSprite(tick, "Square Mesh", "Texture_Default", layer));
		Core::Get().GetComponent<cSprite>(tick)->_colorTint = {1.0f, 1.0f, 1.0f, 0.0f};			//Invisible at start
		Core::Get().AddComponent<cUIElement>(tick, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::TICK, 0));

		ENTITY tickbox = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(tickbox, new cTransform({ posX,posY }, 0, { size,size }));
		Core::Get().AddComponent<cSprite>(tickbox, new cSprite(tickbox, "Square Mesh", "Checkbox", layer));
		Core::Get().GetComponent<cSprite>(tickbox)->_colorTint = { 1.0f, 1.0f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(tickbox, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::TICKBOX, 0));
		Core::Get().GetComponent<cUIElement>(tickbox)->_roleIndex = tick;		//Reference to Tick

		return tickbox;
	}

	ENTITY CreateUI_Option_TickBox_Sound(float posX, float posY, float size, unsigned int layer)
	{
		ENTITY tickbox = CreateUI_TickBox(posX, posY, size, layer);
		Core::Get().GetComponent<cUIElement>(tickbox)->_roleIndex2 = 1;		//Inform the function what to do
		UIEventsManager::Subscribe(tickbox, &OnButtonClick_MainMenuUI);
		return tickbox;
	}
	ENTITY CreateUI_Option_TickBox_Fullscreen(float posX, float posY, float size, unsigned int layer)
	{
		ENTITY tickbox = CreateUI_TickBox(posX, posY, size, layer);
		Core::Get().GetComponent<cUIElement>(tickbox)->_roleIndex2 = 2;		//Inform the function what to do
		UIEventsManager::Subscribe(tickbox, &OnButtonClick_MainMenuUI);
		return tickbox;
	}

	ENTITY CreateBackground_Load()
	{
		ENTITY gamelogo = Create_GameLogo({ 0,100 }, { 500, 300 });
		return gamelogo;
	}

	ENTITY CreateUI_Level1Display()
	{
		ENTITY levelDisplay = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(levelDisplay, new cTransform({ 0,-200 }, 0, { 810 , 120 }));
		Core::Get().AddComponent<cSprite>(levelDisplay, new cSprite(levelDisplay, "Square Mesh", "UI_Mission1", 0));
		return levelDisplay;
	}

	ENTITY CreateUI_Level2Display()
	{
		ENTITY levelDisplay = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(levelDisplay, new cTransform({ 0,-200 }, 0, { 800 , 120 }));
		Core::Get().AddComponent<cSprite>(levelDisplay, new cSprite(levelDisplay, "Square Mesh", "UI_Mission2", 0));
		return levelDisplay;
	}

	ENTITY CreateUI_Level3Display()
	{
		ENTITY levelDisplay = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(levelDisplay, new cTransform({ 0,-200 }, 0, { 800 , 120 }));
		Core::Get().AddComponent<cSprite>(levelDisplay, new cSprite(levelDisplay, "Square Mesh", "UI_Mission3", 0));
		return levelDisplay;
	}


}

namespace Factory_SpashScreen
{
	ENTITY CreateSpashScreen_Digipen()
	{
		ENTITY spashScreen = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(spashScreen, new cTransform({ 0,0 }, 0, {1525 /2, 445/2}));
		Core::Get().AddComponent<cSprite>(spashScreen, new cSprite(spashScreen, "Square Mesh", "DigiPenLogo", 0));
		return spashScreen;
	}

	ENTITY CreateSpashScreen_MoonBase()
	{
		ENTITY spashScreen = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(spashScreen, new cTransform({ 0,0 }, 0, { 612,688 }));
		Core::Get().AddComponent<cSprite>(spashScreen, new cSprite(spashScreen, "Square Mesh", "TeamLogo", 0));
		Core::Get().GetComponent<cSprite>(spashScreen)->_colorTint = { 1.0f, 1.0f, 1.0f, 0.0f };
		Core::Get().GetComponent<cSprite>(spashScreen)->_colorBlend = { 0.9f, 0.9f, 0.9f, 0.2f};
		return spashScreen;
	}
}


namespace Factory_Map
{
	void Generate_StarField()
	{
		if (LevelManager::starfield_Set.size() > 0)	return;

		int numOfStars = 120;
		for (int i = 0; i < numOfStars; ++i)
		{
			float randSize = AERandFloat() * 6;
			float posX = AERandFloat() * 2000 - g_WorldMaxX;

			ENTITY star = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(star, new cTransform({ posX, AERandFloat() * g_WorldMaxY * 2 - g_WorldMaxY }
			, 0, { randSize, randSize }));
			Core::Get().AddComponent<cSprite>(star, new cSprite(star, "Octagon Mesh", "Texture_Default", 6));
			Core::Get().AddComponent<cRigidBody>(star, new cRigidBody(100, AERandFloat() * 100 + 10, 1000));
			Core::Get().GetComponent<cRigidBody>(star)->_velocityDirection = { -1,0 };
			Core::Get().GetComponent<cRigidBody>(star)->_airResistance = 1.0f;		//no air resitatnce
			Core::Get().AddComponent<cWarping>(star, new cWarping({ g_WorldMinX - 200, g_WorldMaxX + 200 }, { g_WorldMinY,g_WorldMaxY }));
			LevelManager::starfield_Set.insert(star);
		}
	}

	void Generate_PlanetField()
	{
		int numOfPlanet = 60;
		for (int i = 0; i < numOfPlanet; ++i)
		{
			int planetType = static_cast<int>(AERandFloat() * 5);

			float scale = AERandFloat() * 100 + 50;

			switch (planetType)
			{
			case 0:
				Factory::CreatePlanet1(2, AERandFloat() * 8000 - g_WorldMaxX * 2, AERandFloat() * 4000 - g_WorldMaxY * 2, scale, scale);
				break;
			case 1:
				Factory::CreatePlanet2(2, AERandFloat() * 8000 - g_WorldMaxX * 2, AERandFloat() * 4000 - g_WorldMaxY * 2, scale, scale);
				break;
			case 2:
				Factory::CreatePlanet3(2, AERandFloat() * 8000 - g_WorldMaxX * 2, AERandFloat() * 4000 - g_WorldMaxY * 2, scale, scale);
				break;
			case 3:
				Factory::CreatePlanet4(2, AERandFloat() * 8000 - g_WorldMaxX * 2, AERandFloat() * 4000 - g_WorldMaxY * 2, scale, scale);
				break;
			case 4:
				Factory::CreateAsteroid1(2, AERandFloat() * 8000 - g_WorldMaxX * 2, AERandFloat() * 4000 - g_WorldMaxY * 2, scale, scale);
				break;
			case 5:
				Factory::CreateAsteroid2(2, AERandFloat() * 8000 - g_WorldMaxX * 2, AERandFloat() * 4000 - g_WorldMaxY * 2, scale, scale);
				break;
			}
		}
	}
}

namespace Factory_AI
{
	ENTITY CreateBoss(AEVec2 pos, ENTITY player, unsigned int layer)
	{
		UNREFERENCED_PARAMETER(player);

		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Boss", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 0.0f, 0.0f, 0.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cBoss>(enemy, new cBoss{ enemy, BOSS });
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, WeaponType::pistol, 5.0f, 0.3f, 5));
		//Core::Get().AddComponent<cHealth>(enemy, new cHealth(2, 3, 5.0f, 2.0f));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(100.0f, 3000.0f, 0.0f, 30.0f, 4.0f, 1.0f));
		Core::Get().GetComponent<cTransform>(enemy)->_position = pos;
		Core::Get().GetComponent<cTransform>(enemy)->_rotation = 0.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 250.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 150.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocity = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.x = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.y = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_acceleration = 5.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityCap = 30.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_tag = COLLISIONTAG::BOSS; // testing collision
		Core::Get().GetComponent<cCollision>(enemy)->_bbShape = ColliderShape::RECTANGLE_OBB;
		Core::Get().GetComponent<cBoss>(enemy)->_currentAttack.attacks.emplace<bossSpawn>();

		// debug ai
		if (g_BBShowMode)	Factory::DebugBoundingBox_Rigidbody(enemy);					//For Collision
		cTransform* aiT = Core::Get().GetComponent<cTransform>(enemy);
		//cAI* aiComp = Core::Get().GetComponent<cAI>(enemy);
		//CreateDebug_Arrow(aiT->_position, aiComp->_blackboard.directionToPlayerN, aiT->_scale.x);
		cRigidBody* rb = Core::Get().GetComponent<cRigidBody>(enemy);
		Factory::CreateDebug_Arrow(aiT->_position, rb->_velocityVector, rb->_velocity);
		return enemy;
	}

	ENTITY CreateEnemy1(ENTITY player, unsigned int layer, AEVec2 spawnPos)
	{
		UNREFERENCED_PARAMETER(player);

		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_1", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI{ enemy, ENEMY });
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, WeaponType::pistol, 3.0f, 0.5f, 2));
		//Core::Get().AddComponent<cHealth>(enemy, new cHealth(2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(0.0f, 30.0f, 0.0f, 30.0f, 4.0f, 1.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = spawnPos.x;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = spawnPos.y;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocity = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.x = -0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.y = 0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_tag = COLLISIONTAG::ENEMY; // testing collision
		Core::Get().GetComponent<cCollision>(enemy)->_bbShape = ColliderShape::RECTANGLE_OBB;
		Core::Get().GetComponent<cAI>(enemy)->_currentState.states.emplace<aiIdle>();



		// debug ai
		if (g_BBShowMode)	Factory::DebugBoundingBox_Rigidbody(enemy);					//For Collision
		cTransform* aiT = Core::Get().GetComponent<cTransform>(enemy);
		//cAI* aiComp = Core::Get().GetComponent<cAI>(enemy);
		//CreateDebug_Arrow(aiT->_position, aiComp->_blackboard.directionToPlayerN, aiT->_scale.x);
		cRigidBody* rb = Core::Get().GetComponent<cRigidBody>(enemy);
		Factory::CreateDebug_Arrow(aiT->_position, rb->_velocityVector, rb->_velocity);
		return enemy;
	}

	ENTITY CreateEnemy2(ENTITY player, unsigned int layer, AEVec2 spawnPos)
	{
		UNREFERENCED_PARAMETER(player);
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_2", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI{ enemy, ENEMY });
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, WeaponType::pistol, 3.0f, 0.5f, 3));
		//Core::Get().AddComponent<cHealth>(enemy, new cHealth(2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(0.0f, 30.0f, 0.0f, 30.0f, 4.0f, 1.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = spawnPos.x;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = spawnPos.y;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocity = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.x = -0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.y = 0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_tag = COLLISIONTAG::ENEMY; // testing collision
		Core::Get().GetComponent<cCollision>(enemy)->_bbShape = ColliderShape::RECTANGLE_OBB;
		Core::Get().GetComponent<cAI>(enemy)->_currentState.states.emplace<aiIdle>();



		// debug ai
		if (g_BBShowMode)	Factory::DebugBoundingBox_Rigidbody(enemy);					//For Collision
		cTransform* aiT = Core::Get().GetComponent<cTransform>(enemy);
		//cAI* aiComp = Core::Get().GetComponent<cAI>(enemy);
		//CreateDebug_Arrow(aiT->_position, aiComp->_blackboard.directionToPlayerN, aiT->_scale.x);
		cRigidBody* rb = Core::Get().GetComponent<cRigidBody>(enemy);
		Factory::CreateDebug_Arrow(aiT->_position, rb->_velocityVector, rb->_velocity);
		return enemy;
	}

	ENTITY CreateEnemy1_2(ENTITY player, unsigned int layer, AEVec2 spawnPos)
	{
		ENTITY enemy = CreateEnemy1(player, layer, spawnPos);
		Core::Get().GetComponent<cRigidBody>(enemy)->_tag = COLLISIONTAG::WAVEENEMY;

		return enemy;
	}

	ENTITY CreateEnemy2_2(ENTITY player, unsigned int layer, AEVec2 spawnPos)
	{
		ENTITY enemy = CreateEnemy2(player, layer, spawnPos);
		Core::Get().GetComponent<cRigidBody>(enemy)->_tag = COLLISIONTAG::WAVEENEMY;

		return enemy;
	}

	ENTITY CreateEnemy2_3(ENTITY player, unsigned int layer, AEVec2 spawnPos)
	{
		ENTITY enemy = CreateEnemy2(player, layer, spawnPos);
		Core::Get().GetComponent<cSprite>(enemy)->LoadTexture("Boss");

		return enemy;
	}

	ENTITY CreateEscort(unsigned int layer, AEVec2 spawnPos)
	{
		ENTITY escort = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(escort, new cTransform({ spawnPos.x , spawnPos.y }, 0.0f, {75.0f, 50.0f}));
		Core::Get().AddComponent<cSprite>(escort, new cSprite(escort, "Square Mesh", "Enemy_1", layer));
		Core::Get().AddComponent<cRigidBody>(escort, new cRigidBody(30.0f, 75.0f, 1000.0f, 0.0f));
		Core::Get().GetComponent<cRigidBody>(escort)->_velocityDirection = { 1.0f, 0.0f };
		Core::Get().GetComponent<cRigidBody>(escort)->_tag = COLLISIONTAG::ESCORT; // testing collision
		Core::Get().AddComponent<cCollision>(escort, new cCollision());

		//Core::Get().AddComponent<cAI>(escort, new cAI);
		//Core::Get().GetComponent<cAI>(escort)->_currentState.states.emplace<aiIdle>();

		Core::Get().AddComponent<cHealth>(escort, new cHealth(0.0f, 100.0f, 0.0f, 100.0f, 0.0f, 1.0f));
		
		return escort;
	}
}

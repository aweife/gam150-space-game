#include "Factory.h"
#include "Core.h"
#include "../Global.h"
#include "../Systems/SystemList.h"
#include "../Managers/ManagerList.h"		
#include "../Global_Graphics.h"	

namespace Factory
{
	ENTITY CreateCamera(ENTITY player)
	{
		ENTITY cameraID = Core::Get().CreateEntity();
		cTransform* playerTransform = Core::Get().GetComponent<cTransform>(player);
		cRigidBody* playerRigidBody = Core::Get().GetComponent<cRigidBody>(player);

		float followSpeed = 300;
		if (playerRigidBody)
		{
			if (playerRigidBody->_velocityCap > 50.0f)
			{
				followSpeed = playerRigidBody->_velocityCap;
			}
		}
		Core::Get().AddComponent<cTransform>(cameraID, new cTransform());
		Core::Get().AddComponent<cCamera>(cameraID, new cCamera(playerTransform, followSpeed));
		CameraManager::AssignNewCam(cameraID);

		return cameraID;
	}

	ENTITY CreatePlayer(unsigned int layer)
	{
		ENTITY player = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(player, new cTransform);
		Core::Get().AddComponent<cSprite>(player, new cSprite(player, "Square Mesh", "Player_1", layer));
		Core::Get().AddComponent<cRigidBody>(player, new cRigidBody(30.0f, 0.0f, 300.0, 3.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(player, new cCollision);
		Core::Get().AddComponent<cSpaceShip>(player, new cSpaceShip(false, 0.5f, 3, 0.0, WeaponMode::range));
		Core::Get().AddComponent<cRangeWeapon>(player, new cRangeWeapon(0.5f));
		Core::Get().AddComponent<cMeleeWeapon>(player, new cMeleeWeapon());
		Core::Get().GetComponent<cRigidBody>(player)->_tag = COLLISIONTAG::PLAYER;
		Core::Get().GetComponent<cCollision>(player)->_bbShape = ColliderShape::RECTANGLE;

		UpgradeManager::WeaponChange(Core::Get().GetComponent<cRangeWeapon>(player)
			, WeaponType::pistol, UpgradePackages::Range_Pistol);

		// Debug
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(player);					//For Collision

		return player;
	}

	ENTITY CreateEnemy1(ENTITY player, unsigned int layer)
	{
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_1", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(3.0f, 0.5f, 2));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = 0.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = -400.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 150.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 100.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocity = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.x = -0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.y = 0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_tag = COLLISIONTAG::ENEMY; // testing collision
		Core::Get().GetComponent<cCollision>(enemy)->_bbShape = ColliderShape::RECTANGLE_OBB;




		// debug ai
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(enemy);					//For Collision
		cTransform* aiT = Core::Get().GetComponent<cTransform>(enemy);
		//cAI* aiComp = Core::Get().GetComponent<cAI>(enemy);
		//CreateDebug_Arrow(aiT->_position, aiComp->_blackboard.directionToPlayerN, aiT->_scale.x);
		cRigidBody* rb = Core::Get().GetComponent<cRigidBody>(enemy);
		CreateDebug_Arrow(aiT->_position, rb->_velocityVector, rb->_velocity);
		return enemy;
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

	void CreateBackground()
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, 0, 0);
		AEVec2Set(&newScale, 1300, 1000);
		ENTITY background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 6));
	}

	ENTITY CreateBullet(float posX, float posY, AEVec2 velocityVector, AEVec2 dir, float rotation)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, 20, 80);

		ENTITY bullet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(bullet, new cTransform(newPostion, rotation, newScale));
		Core::Get().AddComponent<cSprite>(bullet, new cSprite(bullet, "Square Mesh", "Bullet_1", 2));
		Core::Get().AddComponent<cRigidBody>(bullet, new cRigidBody(30.0f, 500.0f, 500.0f));
		Core::Get().AddComponent<cCollision>(bullet, new cCollision);
		Core::Get().GetComponent<cCollision>(bullet)->_bbShape = ColliderShape::RECTANGLE_OBB;
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(bullet);					//For Collision

		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityDirection = dir;
		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityVector = velocityVector;
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

		if (collisionComponent->_bbShape == ColliderShape::RECTANGLE)
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
			{ 20,20 }, 1.0f, { 0.0f,0.0f }, { 0.0f, 1.0f }, 5.0f, 0.0f, 2);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AssignSpawnVariance({ 0 }, { 0 },
			VARIANCETYPE::NONE, { 40,40 }, { 70, 70 }, VARIANCETYPE::RANDOM_UNIFORM, { -1,-1 }, { 1,1 }, VARIANCETYPE::RANDOM);
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 1.0f, 0.9f });
		Core::Get().GetComponent<cParticleEmitter>(emitter)->AddOverLifetime_Color({ 1.0f, 1.0f, 0.0f, 0.9f });
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
}

namespace Factory_UI
{
	ENTITY Create_MM_BeginCampaignUI(AEVec2 position)
	{
		ENTITY begin = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(begin, new cTransform(position, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(begin, new cSprite(begin, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(begin)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(begin, new cUIElement("Play"));
		Core::Get().GetComponent<cUIElement>(begin)->_text._anchor = TEXT_ANCHOR::CENTER;
		UIEventsManager::Subscribe(begin, &OnButtonClick_MainMenuUI);

		return begin;
	}
	ENTITY Create_MM_OptionsUI(AEVec2 position)
	{
		ENTITY options = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(options, new cTransform(position, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(options, new cSprite(options, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(options)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(options, new cUIElement("Options"));
		Core::Get().GetComponent<cUIElement>(options)->_text._anchor = TEXT_ANCHOR::CENTER;
		//UIEventsManager::Subscribe(options, &OnButtonClick_MainMenuUI);
		return 0;

	}
	ENTITY Create_MM_CreditsUI(AEVec2 position)
	{
		ENTITY credits = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(credits, new cTransform(position, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(credits, new cSprite(credits, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(credits)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(credits, new cUIElement("Credits"));
		Core::Get().GetComponent<cUIElement>(credits)->_text._anchor = TEXT_ANCHOR::CENTER;
		//UIEventsManager::Subscribe(credits, &OnButtonClick_MainMenuUI);
		return 0;
	}
	ENTITY Create_MM_Quit(AEVec2 position)
	{
		ENTITY quit = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(quit, new cTransform(position, 0, { 160, 40 }));
		Core::Get().AddComponent<cSprite>(quit, new cSprite(quit, "Square Mesh", "Texture_Default", 0));
		Core::Get().GetComponent<cSprite>(quit)->_colorTint = { 1.0f, 0.28f, 0.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(quit, new cUIElement("Quit"));
		Core::Get().GetComponent<cUIElement>(quit)->_text._anchor = TEXT_ANCHOR::CENTER;
		//UIEventsManager::Subscribe(quit, &OnButtonClick_MainMenuUI);
		return 0;
	}

	ENTITY Create_GameLogo(AEVec2 position, AEVec2 scale)
	{
		ENTITY gameLogo = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(gameLogo, new cTransform(position, 0, scale));
		Core::Get().AddComponent<cSprite>(gameLogo, new cSprite(gameLogo, "Square Mesh", "GameLogo", 6));
		return gameLogo;
	}

	//Placed here so that all the leves UI will be standardised in case of change
	//This includes health bar, shield bar and thruster fuel
	void Create_PlayerUserInterface()
	{
		AEVec2 spritePos;
		for (int i = 0; i < 3; ++i)
		{
			spritePos = ScreenBasedCoords(100.0f + 50.0f * i, -75.0f, UI_ANCHOR::TOPLEFT);
			Create_SingleHealthBar(spritePos, i);
		}

		spritePos = ScreenBasedCoords(-150.0f, -75.0f, UI_ANCHOR::TOPRIGHT);
		Create_ThrusterUI(spritePos);

		spritePos = ScreenBasedCoords(0.0f, 0.0f, UI_ANCHOR::CENTER);
		ENTITY group[9] = { 0 };
		//Create_ChooseThree(spritePos, group);
	}

	ENTITY Create_SingleHealthBar(AEVec2 position, int i)
	{
		ENTITY hpBar = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(hpBar, new cTransform(position, 0, { 50, 50 }));
		Core::Get().AddComponent<cSprite>(hpBar, new cSprite(hpBar, "UI_HP bar", "HP_FILL", 0));
		Core::Get().GetComponent<cSprite>(hpBar)->_colorTint = { 1.0f,0, 0.2f,0.8f };
		Core::Get().AddComponent<cUIElement>(hpBar, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::HEALTH, i));
		UIEventsManager::Subscribe(hpBar, &OnHealthChange_HPUI);
		//UIEventsManager::UnSubscribe<Events::OnHealthChange>(hpBar);

		/*ENTITY effect = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(effect, new cTransform(position, 0, { 50, 50 }));
		Core::Get().AddComponent<cSprite>(effect, new cSprite(effect, "UI_HP bar", "Planet_1", 0));
		Core::Get().GetComponent<cSprite>(effect)->_colorTint = { 1.0f, 1.0, 1.0f,0.2f };
		Core::Get().GetComponent<cSprite>(effect)->_blend = AE_GFX_BM_ADD;*/

		return hpBar;
	}

	ENTITY Create_ThrusterUI(AEVec2 position)
	{
		ENTITY thruster = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(thruster, new cTransform(position, 0, { 1, 1 }));			//mesh scale of 50
		Core::Get().AddComponent<cSprite>(thruster, new cSprite(thruster, "UI_Thruster", "Texture_Fill", 0));
		Core::Get().GetComponent<cSprite>(thruster)->_colorTint = { 1.0f,1.0f, 0.0f,0.8f };
		Core::Get().AddComponent<cUIElement>(thruster, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::THRUSTER));
		//UIEventsManager::Subscribe(hpBar, &OnHealthChange_HPUI);

		return thruster;
	}


	void Create_ChooseThree(AEVec2 centralPos, ENTITY(&group)[9])
	{
		ENTITY border = 0, fakeupgrade, upgrade = 0, title = 0, text = 0, comfirm;
		float borderSize = 100, borderSpace = 10;
		AEVec2 startingPos;
		AEVec2Set(&centralPos, centralPos.x - borderSize - borderSpace, centralPos.y);

		for (int i = 0; i < 3; ++i)
		{
			AEVec2Set(&startingPos, centralPos.x + (borderSize + borderSpace) * i, centralPos.y);
			border = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(border, new cTransform(startingPos, 0.0f, { borderSize , borderSize }));
			Core::Get().AddComponent<cSprite>(border, new cSprite(border, "Square Mesh", "Texture_Default", 0));
			Core::Get().AddComponent<cUIElement>(border, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_FRAME));
			group[i] = border;

			AEVec2Set(&startingPos, startingPos.x, centralPos.y + (borderSize * 0.9f) / 2 - (borderSize * 0.9f) * (1.0f / 10)); //start small and expand
			upgrade = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(upgrade, new cTransform(startingPos, 0.0f, { borderSize * 0.9f, (2.0f / 10) * borderSize }));
			Core::Get().AddComponent<cSprite>(upgrade, new cSprite(upgrade, "Square Mesh", "Texture_Default", 0));
			Core::Get().GetComponent<cSprite>(upgrade)->_colorTint = { 1.0f,0.0f, 0.0f,1.0f };
			Core::Get().AddComponent<cUIElement>(upgrade, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_UPGRADE));
			group[i + 1] = upgrade;

			AEVec2Set(&startingPos, startingPos.x, centralPos.y + (borderSize * 0.9f) / 2 - (borderSize * 0.9f) * (6.0f / 10));
			fakeupgrade = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(fakeupgrade, new cTransform(startingPos, 0.0f, { borderSize * 0.9f, (8.0f / 10) * borderSize }));
			Core::Get().AddComponent<cSprite>(fakeupgrade, new cSprite(fakeupgrade, "Square Mesh", "Texture_Default", 0));
			Core::Get().GetComponent<cSprite>(fakeupgrade)->_colorTint = { 0.0f,0.0f, 1.0f,1.0f };
			Core::Get().AddComponent<cUIElement>(fakeupgrade, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_FAKEUPGRADE));
			group[i + 2] = fakeupgrade;

		}
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

	ENTITY CreateBackground_Load()
	{
		ENTITY gamelogo = Create_GameLogo({ 0,100 }, { 500, 300 });
		return gamelogo;
	}
}
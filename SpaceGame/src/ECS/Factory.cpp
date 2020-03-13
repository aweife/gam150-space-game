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

		float followSpeed = 300.0f;
		if (playerRigidBody)
		{
			if (playerRigidBody->_velocityCap > 50.0f)
			{
				followSpeed = playerRigidBody->_velocityCap;
			}
		}
		Core::Get().AddComponent<cTransform>(cameraID, new cTransform());
		Core::Get().AddComponent<cCamera>(cameraID, new cCamera(playerTransform, 400.0f));
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
		CreateParticleEmitter_TRAILSTATIC(Core::Get().GetComponent<cTransform>(player));
		return player;
	}

	ENTITY CreatePlayer(unsigned int layer)
	{
		ENTITY player = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(player, new cTransform);
		Core::Get().AddComponent<cSprite>(player, new cSprite(player, "Square Mesh", "Player_1", layer));
		Core::Get().AddComponent<cRigidBody>(player, new cRigidBody(3.0f, 0.0f, 75.0, 3.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(player, new cCollision);
		Core::Get().AddComponent<cSpaceShip>(player, new cSpaceShip(false, 0.5f, 3, WeaponMode::range));
		Core::Get().AddComponent<cRangeWeapon>(player, new cRangeWeapon(OWNERTAG::PLAYER, 0.4f));
		Core::Get().AddComponent<cMeleeWeapon>(player, new cMeleeWeapon());
		//Core::Get().AddComponent<cHealth>(player, new cHealth(2.0f, 3.0f, 2.0f, 3.0f, 5.0f,2.0f));

		Core::Get().GetComponent<cRigidBody>(player)->_tag = COLLISIONTAG::PLAYER;
		Core::Get().GetComponent<cCollision>(player)->_bbShape = ColliderShape::RECTANGLE;

		/* UpgradeManager::WeaponChange(Core::Get().GetComponent<cRangeWeapon>(player)
			, WeaponType::pistol, UpgradePackages::Range_Pistol); */
		Core::Get().AddComponent<cHealth>(player, new cHealth(30.0f, 30.0f, 30.0f, 30.0f, 4.0f, 1.0f));
		Factory_UI::Create_ShieldBubble();
		// Debug
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(player);					//For Collision

		Core::Get().GetComponent<cTransform>(player)->_scale.x = 50.0f;
		Core::Get().GetComponent<cTransform>(player)->_scale.y = 50.0f;

		return player;
	}

	ENTITY CreateEnemy1(ENTITY player, unsigned int layer)
	{
		UNREFERENCED_PARAMETER(player);

		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_1", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, 3.0f, 0.5f, 1));
		//Core::Get().AddComponent<cHealth>(enemy, new cHealth(2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(0.0f, 30.0f, 0.0f, 30.0f, 4.0f, 1.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = 0.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = -400.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
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

	ENTITY CreateEnemy2(ENTITY player, unsigned int layer)
	{
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_2", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, 3.0f, 0.5f, 2));
		//Core::Get().AddComponent<cHealth>(enemy, new cHealth(2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(0.0f, 30.0f, 0.0f, 30.0f, 4.0f, 1.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = 0.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = 400.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
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

	ENTITY CreateEnemy3(ENTITY player, unsigned int layer)
	{
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_1", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, 3.0f, 0.5f, 2));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(2, 3, 5.0f, 2.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = 1500.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = 1800.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
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

	ENTITY CreateEnemy4(ENTITY player, unsigned int layer)
	{
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_2", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, 3.0f, 0.5f, 2));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(2, 3, 5.0f, 2.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = 1200.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = 1500.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
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

	ENTITY CreateEnemy5(ENTITY player, unsigned int layer)
	{
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_2", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 50.0f, 100.0f, 2.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().AddComponent<cRangeWeapon>(enemy, new cRangeWeapon(OWNERTAG::AI, 3.0f, 0.5f, 2));
		Core::Get().AddComponent<cHealth>(enemy, new cHealth(2, 3, 5.0f, 2.0f));

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = -1800.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = -2000.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 75.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 50.0f;
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
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 7));
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
		Core::Get().AddComponent<cSprite>(gameLogo, new cSprite(gameLogo, "Square Mesh", "GameLogo", 0));
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

		for (int i = 0; i < 3; ++i)
		{
			spritePos = ScreenBasedCoords(250.0f + 50.0f * i, -75.0f, UI_ANCHOR::TOPLEFT);
			Create_SingleShieldBar(spritePos, i);
		}

		spritePos = ScreenBasedCoords(-150.0f, -75.0f, UI_ANCHOR::TOPRIGHT);
		Create_ThrusterUI(spritePos);

		spritePos = ScreenBasedCoords(0.0f, 0.0f, UI_ANCHOR::CENTER);
		//Create_ChooseThree(spritePos);
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
		Core::Get().AddComponent<cTransform>(shieldBubble, new cTransform({0,0}, 0, { 100, 100 }));
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
		Core::Get().AddComponent<cTransform>(thruster, new cTransform(position, 0, { 1, 1 }));			//mesh scale of 50
		Core::Get().AddComponent<cSprite>(thruster, new cSprite(thruster, "UI_Thruster", "Texture_Fill", 0));
		Core::Get().GetComponent<cSprite>(thruster)->_colorTint = { 1.0f,1.0f, 0.0f,0.8f };
		Core::Get().AddComponent<cUIElement>(thruster, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::THRUSTER));
		//UIEventsManager::Subscribe(hpBar, &OnHealthChange_HPUI);

		return thruster;
	}


	void Create_ChooseThree(AEVec2 centralPos)
	{
		ENTITY border = 0, fakeupgrade = 0;
		float borderSize = 100, borderSpace = 10;
		AEVec2 startingPos;
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
			Core::Get().AddComponent<cTransform>(fakeupgrade, new cTransform(startingPos, 0.0f, {borderSize * 0.9f, borderSize * 0.9f}));
			Core::Get().AddComponent<cSprite>(fakeupgrade, new cSprite(fakeupgrade, "Square Mesh2", "Random_Upgrade", 0));
			Core::Get().GetComponent<cSprite>(fakeupgrade)->_colorTint = { 0.0f, 0.0f, 1.0f, 1.0f };
			Core::Get().AddComponent<cUIElement>(fakeupgrade, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_FAKEUPGRADE));

			Core::Get().AddComponent<cTimeline>(fakeupgrade, new cTimeline(g_appTime, g_appTime + 0.5f + (i * 0.5f), false));
			AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(fakeupgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(fakeupgrade));
			AddNewNode_Float(&Core::Get().GetComponent<cSprite>(fakeupgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(fakeupgrade), 0.45f + (i * 0.5f), -1.5f * (i+2));
			AddNewTimeline_Void(Create_ChoosableUpgrade, Core::Get().GetComponent<cTimeline>(fakeupgrade));
			AddNewNode_Void(Create_ChoosableUpgrade, Core::Get().GetComponent<cTimeline>(fakeupgrade), 0.49f + (i * 0.5f), fakeupgrade);
		}
	}

	void Create_ChoosableUpgrade(ENTITY entity)
	{
		AEVec2 position = Core::Get().GetComponent<cTransform>(entity)->_position;
		ENTITY realUpgrade = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(realUpgrade, new cTransform(position, 0.0f, { 100 * 0.9f, 100 * 0.9f }));
		Core::Get().AddComponent<cSprite>(realUpgrade, new cSprite(realUpgrade, "Square Mesh2", "Upgrade_1", 0));
		Core::Get().GetComponent<cSprite>(realUpgrade)->_colorTint = { 0.0f, 0.0f, 1.0f, 1.0f };
		Core::Get().AddComponent<cUIElement>(realUpgrade, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::C3_UPGRADE));

		Core::Get().AddComponent<cTimeline>(realUpgrade, new cTimeline(g_appTime, g_appTime + 0.5f, false));
		AddNewTimeline_Float(&Core::Get().GetComponent<cSprite>(realUpgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(realUpgrade));
		AddNewNode_Float(&Core::Get().GetComponent<cSprite>(realUpgrade)->_UVOffset.y, Core::Get().GetComponent<cTimeline>(realUpgrade), 0.45f, -0.5f );
	}

	ENTITY Create_AIIndicator(ENTITY ai, AEVec2 aiDir, int aiType)
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

		ENTITY aiUI = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(aiUI, new cTransform(aiDir, angle, { 100,100 }));
		Core::Get().AddComponent<cSprite>(aiUI, new cSprite(aiUI, "Square Mesh", "AI_Indicator", 0));
		if (aiType == 0)
		{
		}
		else if (aiType == 1)
		{
			Core::Get().GetComponent<cSprite>(aiUI)->_colorTint.g = 0.0f;
			Core::Get().GetComponent<cSprite>(aiUI)->_colorTint.b = 0.0f;
		}
		Core::Get().AddComponent<cUIElement>(aiUI, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::INDICATE_AI, ai));
		return aiUI;
	}

	void CreateUI_GameOver()
	{
		ENTITY panel = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(panel, new cTransform({0,0}, 0, { 800,300 }));
		Core::Get().AddComponent<cSprite>(panel, new cSprite(panel, "Square Mesh", "Texture_Default", 0));
		Core::Get().AddComponent<cUIElement>(panel, new cUIElement(UI_TYPE::IMAGE, UI_ROLE::GAMEOVER, 0));
		Core::Get().GetComponent<cSprite>(panel)->_colorTint = { 0.0f, 0.0f, 0.0f, 1.0f };

		ENTITY text = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(text, new cTransform({ 0,50 }, 0, { 1, 1}));
		Core::Get().AddComponent<cUIElement>(text, new cUIElement("GAME OVER"));
		Core::Get().GetComponent<cUIElement>(text)->_role = UI_ROLE::GAMEOVER;
		Core::Get().GetComponent<cUIElement>(text)->_roleIndex = 1;
		Core::Get().GetComponent<cUIElement>(text)->_text._anchor = TEXT_ANCHOR::CENTER;

		ENTITY text2 = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(text2, new cTransform({ 0,-100 }, 0, { 1, 1 }));
		Core::Get().AddComponent<cUIElement>(text2, new cUIElement("Press Esc To Return to Main Menu"));
		Core::Get().GetComponent<cUIElement>(text2)->_role = UI_ROLE::GAMEOVER;
		Core::Get().GetComponent<cUIElement>(text2)->_roleIndex = 2;
		Core::Get().GetComponent<cUIElement>(text2)->_text._anchor = TEXT_ANCHOR::CENTER;
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

namespace Factory_Map
{
	void Generate_StarField_Menu()
	{
		int numOfStars = 120;
		for (int i = 0; i < numOfStars; ++i)
		{
			float randSize = AERandFloat() * 6;
			float posX = AERandFloat() * 2000 - g_WorldMaxX;

			ENTITY star = Core::Get().CreateEntity();
			Core::Get().AddComponent<cTransform>(star, new cTransform({ posX, AERandFloat() * g_WorldMaxY * 2 - g_WorldMaxY }
			, 0, { randSize, randSize }));
			Core::Get().AddComponent<cSprite>(star, new cSprite(star, "Octagon Mesh", "Texture_Default", 6));
			Core::Get().AddComponent<cRigidBody>(star, new cRigidBody(100, AERandFloat() * 50 + 10, 100));
			Core::Get().GetComponent<cRigidBody>(star)->_velocityDirection = {-1,0};
			Core::Get().GetComponent<cRigidBody>(star)->_airResistance = 1.0f;		//no air resitatnce
			Core::Get().AddComponent<cWarping>(star, new cWarping({ -2000, g_WorldMaxX}, { 0,0 }));
		
		}
	}

	void Generate_StarField()
	{

	}
}
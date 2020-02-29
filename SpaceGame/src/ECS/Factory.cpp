#include "Factory.h"
#include "Core.h"
#include "../Global.h"

#include "../Managers/CameraManager.h"

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
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(player);					//For Collision
		Core::Get().AddComponent<cSpaceShip>(player, new cSpaceShip);

		return player;
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
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(planet);
		Core::Get().GetComponent<cRigidBody>(planet)->_velocity = 0;
		//Core::Get().AddComponent<cCollision>(planet, new cCollision);

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

	ENTITY CreateEnemy1(ENTITY player, unsigned int layer)
	{
		ENTITY enemy = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(enemy, new cTransform);
		Core::Get().AddComponent<cSprite>(enemy, new cSprite(enemy, "Square Mesh", "Enemy_1", layer));
		Core::Get().AddComponent<cRigidBody>(enemy, new cRigidBody(30.0f, 2.0f, 2.0f, 0.0f));
		Core::Get().AddComponent<cCollision>(enemy, new cCollision);
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(enemy);					//For Collision
		Core::Get().AddComponent<cPathFinding>(enemy, new cPathFinding);
		Core::Get().AddComponent<cAI>(enemy, new cAI);
		Core::Get().GetComponent<cAI>(enemy)->minDistance = 250.0f;
		Core::Get().GetComponent<cAI>(enemy)->maxDistance = 500.0f;

		Core::Get().GetComponent<cTransform>(enemy)->_position.x = 0.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_position.y = -200.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.x = 100.0f;
		Core::Get().GetComponent<cTransform>(enemy)->_scale.y = 150.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocity = 0.0f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.x = -0.5f;
		Core::Get().GetComponent<cRigidBody>(enemy)->_velocityVector.y = 0.5f;
		Core::Get().GetComponent<cPathFinding>(enemy)->target = player;
		Core::Get().GetComponent<cPathFinding>(enemy)->currentState = PATH_SEEK;
		Core::Get().GetComponent<cCollision>(enemy)->name = "ENEMY";
		return enemy;
	}

	void CreateBackground()
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, 0, 0);
		AEVec2Set(&newScale, 1300, 1000);
		ENTITY background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 6));

		AEVec2Set(&newPostion, 1300, 0);
		background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 6));

		AEVec2Set(&newPostion, -1300, 0);
		background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 6));

		AEVec2Set(&newPostion, 0, 1300);
		background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 6));

		AEVec2Set(&newPostion, 0, -1300);
		background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_1", 6));
	}


	ENTITY CreateBackground_Load()
	{
		ENTITY background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform({ 0,0 }, 0, { 1000, 1000 }));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "Square Mesh", "BG_Loading", 6));
		return background;
	}

	ENTITY CreateBullet(float posX, float posY, AEVec2 velocityVector, float rotation)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, 20, 80);

		ENTITY bullet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(bullet, new cTransform(newPostion, rotation, newScale));
		Core::Get().AddComponent<cSprite>(bullet, new cSprite(bullet, "Square Mesh", "Bullet_1", 2));
		Core::Get().AddComponent<cRigidBody>(bullet, new cRigidBody(30.0f, 500.0f, 500.0f));
		//Core::Get().AddComponent<cCollision>(bullet, new cCollision);
		if (g_BBShowMode)	DebugBoundingBox_Rigidbody(bullet);					//For Collision

		Core::Get().GetComponent<cRigidBody>(bullet)->_velocityVector = velocityVector;

		return bullet;
	}

	ENTITY CreateUI_Text(float posX, float posY, const char* text)
	{
		AEVec2 newPostion;
		AEVec2Set(&newPostion, posX, posY);

		ENTITY uiEntity = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(uiEntity, new cTransform(newPostion, 0, {1,1}));
		Core::Get().AddComponent<cUIElement>(uiEntity, new cUIElement(text));
		return uiEntity;
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
		cRigidBody* rbComponent = Core::Get().GetComponent<cRigidBody>(target);
		cTransform* transformComponent = Core::Get().GetComponent<cTransform>(target);
		ENTITY boundingBox;

		if (1)
		{
			boundingBox = Factory::CreateDebug_Square(transformComponent->_position, transformComponent->_rotation,
				transformComponent->_scale);
		}

		return boundingBox;
	}
}


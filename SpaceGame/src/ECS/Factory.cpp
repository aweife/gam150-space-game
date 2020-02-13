#include "Factory.h"
#include "Core.h"
#include "../Components/ComponentList.h"
#include "../Managers/CameraManager.h"

namespace Factory
{
	ENTITY CreateCamera(ENTITY player, float followSpeed)
	{
		ENTITY cameraID = Core::Get().CreateEntity();
		cTransform* playerTransform = Core::Get().GetComponent<cTransform>(player);

		Core::Get().AddComponent<cTransform>(cameraID, new cTransform());
		Core::Get().AddComponent<cCamera>(cameraID, new cCamera(playerTransform, followSpeed));
		CameraManager::AssignNewCam(cameraID);

		return cameraID;
	}

	ENTITY CreatePlayer(unsigned int layer)
	{
		ENTITY player = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(player, new cTransform);
		Core::Get().AddComponent<cSprite>(player, new cSprite(player, "res/Player_MachineGun.png", layer));
		Core::Get().AddComponent<cRigidBody>(player, new cRigidBody);
		Core::Get().GetComponent<cRigidBody>(player)->velocity.x = 2;
		Core::Get().AddComponent<cCollision>(player, new cCollision);

		return player;
	}

	ENTITY CreatePlanet1(unsigned int layer, float posX, float posY, float scaleX, float scaleY)
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, posX, posY);
		AEVec2Set(&newScale, scaleX, scaleY);

		ENTITY planet = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(planet, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "res/Prop_Planet1.png", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody);
		Core::Get().GetComponent<cRigidBody>(planet)->velocity.x = 0;
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
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "res/Prop_Planet2.png", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody);
		Core::Get().GetComponent<cRigidBody>(planet)->velocity.x = 0;
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
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "res/Prop_Planet3.png", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody);
		Core::Get().GetComponent<cRigidBody>(planet)->velocity.x = 0;
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
		Core::Get().AddComponent<cSprite>(planet, new cSprite(planet, "res/Prop_Planet4.png", layer));
		Core::Get().AddComponent<cRigidBody>(planet, new cRigidBody);
		Core::Get().GetComponent<cRigidBody>(planet)->velocity.x = 0;
		//Core::Get().AddComponent<cCollision>(planet, new cCollision);

		return planet;
	}

	ENTITY CreateBackground()
	{
		AEVec2 newPostion, newScale;
		AEVec2Set(&newPostion, 0, 0);
		AEVec2Set(&newScale, 13000, 10000);

		ENTITY background = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(background, new cTransform(newPostion, 0, newScale));
		Core::Get().AddComponent<cSprite>(background, new cSprite(background, "res/BG_Background1.png", 6));

		return background;
	}
}


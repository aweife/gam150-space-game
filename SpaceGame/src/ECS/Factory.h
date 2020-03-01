#pragma once
#include "../Global_ECS.h"
#include "AEEngine.h"
#include "../Tools/MemoryLeak.h"
#include "../Components/ComponentList.h"

namespace Factory
{
	ENTITY CreateCamera(ENTITY player);
	ENTITY CreatePlayer(unsigned int layer);
	ENTITY CreatePlanet1(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet2(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet3(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet4(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreateEnemy1(ENTITY player, unsigned int layer);
	void CreateBackground();
	ENTITY CreateBackground_Load();
	ENTITY CreateBullet(float posX, float posY, AEVec2 velocityVector, float rotation);

	ENTITY CreateUI_Text(float posX, float posY, const char* text);
	ENTITY CreateDebug_Arrow(AEVec2& pos, AEVec2& rot, float& scale);
	ENTITY CreateDebug_Line(AEVec2& start, AEVec2& end);
	ENTITY CreateDebug_Square(AEVec2& pos, float& rot, AEVec2& scale);
	ENTITY CreateDebug_Octagon(AEVec2& pos, float& rot, AEVec2& scale);
	ENTITY DebugVector_Velocity(ENTITY target);
	ENTITY DebugBoundingBox_Rigidbody(ENTITY target);

	ENTITY CreateParticleEmitter_MYFIRST();
}

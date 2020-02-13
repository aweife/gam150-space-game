#pragma once
#include "../Global_ECS.h"

namespace Factory
{
	ENTITY CreateCamera(ENTITY player, float followSpeed);
	ENTITY CreatePlayer(unsigned int layer);
	ENTITY CreatePlanet1(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet2(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet3(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	ENTITY CreatePlanet4(unsigned int layer, float posX, float posY, float scaleX, float scaleY);
	void CreateBackground();
}

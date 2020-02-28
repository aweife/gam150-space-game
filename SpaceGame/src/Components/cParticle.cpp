//25/2/2020

#include "cParticle.h"
#include "../Managers/ResourceManager.h"


cParticle::cParticle(const char* meshName, const char* textureName, ColorInfo color, float scaleFactor, 
	float warmUpTime, float totalLifeTime, AEVec2 gravity, AEVec2 velocity, ColorInfo colorVar, float scaleVar, AEVec2 velocityVar)
	:_texture{ nullptr }, _currColor {color}, _scaleFactor{ scaleFactor }, _warmUpTime{ warmUpTime }, _totalLifeTime{ totalLifeTime }, _gravity{ gravity },
	_velocityBase{velocity}, _colorVariance{colorVar}, _scaleVariance{scaleVar}, _velocityVariance{velocityVar}
{
	LoadMesh(meshName);
	if (strcmp(textureName, "None") != 0)
	{
		LoadTexture(textureName);
	}
	
}

void cParticle::LoadMesh(const char* meshName)
{
	AE_ASSERT_MESG(ResourceManager::meshLibrary.find(meshName) != ResourceManager::meshLibrary.end(), "Failed to find Mesh!");

	_mesh = ResourceManager::meshLibrary[meshName];
}

void cParticle::LoadTexture(const char* textureName)
{
	AE_ASSERT_MESG(ResourceManager::textureLibrary.find(textureName) != ResourceManager::textureLibrary.end(), "Failed to find Texture!");

	_texture = ResourceManager::textureLibrary[textureName];
}

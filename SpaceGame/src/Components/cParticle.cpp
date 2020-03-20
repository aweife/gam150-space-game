//25/2/2020

#include "cParticle.h"
#include "../Managers/ResourceManager.h"
#include "../ECS/Core.h"
#include "../Components/cParticleEmitter.h"

cParticle::cParticle(const char* meshName, const char* textureName, ColorInfo color, AEVec2 scaleFactor
	, float totalLifeTime, AEVec2 gravity, AEVec2 direction, float velocity, ENTITY emitterID, float rotation,  unsigned int layer)
	:_particleData{ color, scaleFactor, totalLifeTime, 0.0f, gravity, {0,0}, direction, velocity, rotation, layer }, _mesh{ nullptr },
	_texture{ nullptr }, _emitterID{ emitterID }, _isAlive{true}, _isVisible{true}
{
	LoadMesh(meshName);
	if (strcmp(textureName, "None") != 0)
	{
		LoadTexture(textureName);
	}
}

void cParticle::AddOverLifetime_Color(ColorInfo colorVar)
{
	_particleData._colorOverLifetime.push_back(colorVar);
}
void cParticle::AddOverLifetime_Scale(AEVec2 scaleVar)
{
	_particleData._scaleOverLifetime.push_back(scaleVar);
}
void cParticle::AddOverLifetime_Direction(AEVec2 directionVar)
{
	_particleData._directionOverLifetime.push_back(directionVar);
}
void cParticle::AddOverLifetime_Velocity(float velocityVar)
{
	_particleData._velocityOverLifetime.push_back(velocityVar);
}

void cParticle::AddOverLifetime_Rotation(float rotation)
{
	_particleData._rotationOverLifetime.push_back(rotation);
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

cParticle::~cParticle()
{
	cParticleEmitter* myEmitter =  Core::Get().GetComponent<cParticleEmitter>(_emitterID);
}
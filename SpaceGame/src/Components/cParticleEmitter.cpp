/**********************************************************************************
* \file			cParticleEmitter.cpp
* \brief		Paticle Emitter
* \author		Jun Yi,				Chong,  100% Code Contribution
*
*				Handles the particle emitter component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cParticleEmitter.h"
#include "../Global.h"

cParticleEmitter::cParticleEmitter(AEVec2 spawnPos, float radius, float spawnRateMin, float spawnRateMax, float lifeTime 
	,int spawnAmount, float nextSpawn, float warmupTime, float loopTime, float currTime, unsigned int particleCap)
	:_spawnPositionOffset{spawnPos}, _emissionRadius{radius} , _spawnRateCurr{ nextSpawn }, _spawnAmount{ spawnAmount }
	, _lastSpawnTime{ g_appTime }, _spawnMeshName{ "" }, _spawnTextureName{ "None" }, _spawnRateVarType{VARIANCETYPE::RANDOM}
	, _warmUpTime{ warmupTime }, _loopTime{ loopTime }, _currTime{ currTime }, _lifeTime{ lifeTime }, _currlifeTime{0.0f}
	, _isAlive{true}, _particleCap{particleCap}
{
	_spawnRateVariance[0] = spawnRateMin;
	_spawnRateVariance[1] = spawnRateMax;
}

void cParticleEmitter::AssignParticleSpawnInfo(const char* meshName, const char* textureName, ColorInfo color, AEVec2 scaleFactor
	, float totalLifeTime, AEVec2 gravity, AEVec2 direction, float velocity, float rotation, unsigned int layer)
{
	_spawnMeshName = meshName;
	_spawnTextureName = textureName;

	_particleToSpawn._currColor = color;
	_particleToSpawn._scaleFactor = scaleFactor;
	_particleToSpawn._totalLifeTime = totalLifeTime;
	_particleToSpawn._currLifeTime = 0.0f;
	_particleToSpawn._gravity = gravity;
	_particleToSpawn._direction = direction;
	_particleToSpawn._velocityBase = velocity;
	_particleToSpawn._rotation = rotation;
	_particleToSpawn._layer = layer;
}

void cParticleEmitter::AssignSpawnVariance(ColorInfo c1, ColorInfo c2, VARIANCETYPE colorVarType, AEVec2 scale1, AEVec2 scale2
	, VARIANCETYPE scaleVarType, AEVec2 dir1, AEVec2 dir2, VARIANCETYPE dirVarType, float velocity1, float velocity2
	, VARIANCETYPE velocityVarType, float spawnRate1, float spawnRate2, VARIANCETYPE spawnRateVarType 
	,float lifeTime1, float lifeTime2, VARIANCETYPE spawnLifeTimeVarType)
{
	_colorVariance[0] = c1;
	_colorVariance[1] = c2;
	_scaleVariance[0] = scale1;
	_scaleVariance[0] = scale2;
	_directionVariance[0] = dir1;
	_directionVariance[1] = dir2;
	_velocityVariance[0] = velocity1;
	_velocityVariance[1] = velocity2;
	_spawnRateVariance[0] = spawnRate1;
	_spawnRateVariance[0] = spawnRate2;
	_lifeTimeVariance[0] = lifeTime1;
	_lifeTimeVariance[1] = lifeTime2;
	_spawnColorVarType = colorVarType;
	_spawnScaleVarType = scaleVarType;
	_spawnDirectionVarType = dirVarType;
	_spawnVelocityVarType = velocityVarType;
	_spawnRateVarType = spawnRateVarType;
	_spawnLifeTimeVarType = spawnLifeTimeVarType;
}

void cParticleEmitter::AddOverLifetime_Color(ColorInfo colorVar)
{
	_particleToSpawn._colorOverLifetime.push_back(colorVar);
}
void cParticleEmitter::AddOverLifetime_Scale(AEVec2 scaleVar)
{
	_particleToSpawn._scaleOverLifetime.push_back(scaleVar);
}
void cParticleEmitter::AddOverLifetime_Direction(AEVec2 directionVar)
{
	_particleToSpawn._directionOverLifetime.push_back(directionVar);
}
void cParticleEmitter::AddOverLifetime_Velocity(float velocityVar)
{
	_particleToSpawn._velocityOverLifetime.push_back(velocityVar);
}

void cParticleEmitter::AddOverLifetime_Rotation(float rotation)
{
	_particleToSpawn._rotationOverLifetime.push_back(rotation);
}

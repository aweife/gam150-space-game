/**********************************************************************************
* \file			cParticleEmitter.h
* \brief		Paticle Emitter
* \author		Jun Yi,				Chong,  100% Code Contribution
*
*				Handles the particle emitter data
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "Component.h"					//Base Class
#include "AEEngine.h"
#include "cParticle.h"
#include <queue>

enum class VARIANCETYPE
{
	NONE,
	RANDOM,
	RANDOM_UNIFORM,
	CURVE
};


class cParticleEmitter :public Component
{
public:
	//Data
	std::queue<ENTITY> _particlePool;
	std::queue<ENTITY> _recycleParticlePool;							//Subset of particlePool
	ParticleInfo _particleToSpawn = { 0 };
	const char*  _spawnMeshName;
	const char*  _spawnTextureName;

	ColorInfo	 _colorVariance[2]		=	{0};
	AEVec2		 _scaleVariance[2]		=	{0};
	AEVec2		 _directionVariance[2]	=	{0};
	float		 _velocityVariance[2]	=	{0};
	float		 _spawnRateVariance[2]	=	{0};
	float		 _lifeTimeVariance[2]	= { 0 };
	VARIANCETYPE _spawnColorVarType		= VARIANCETYPE::NONE;
	VARIANCETYPE _spawnScaleVarType		= VARIANCETYPE::NONE;
	VARIANCETYPE _spawnDirectionVarType	= VARIANCETYPE::NONE;
	VARIANCETYPE _spawnVelocityVarType	= VARIANCETYPE::NONE;
	VARIANCETYPE _spawnRateVarType		= VARIANCETYPE::RANDOM;
	VARIANCETYPE _spawnLifeTimeVarType	= VARIANCETYPE::NONE;

	AEVec2 _spawnPositionOffset = { 0, 0 };					//Relative to transform
	float _emissionRadius = 0.0f;
	float _spawnRateCurr = 0.0f;
	int _spawnAmount = 1;
	float _lastSpawnTime = 0.0f;
	float _warmUpTime;
	float _loopTime;
	float _currTime;
	float _lifeTime;
	float _currlifeTime;
	bool _isAlive;
	unsigned int _particleCap;

	// Constructor with parameter
	cParticleEmitter() = delete;
	cParticleEmitter(AEVec2 spawnPos, float radius, float spawnRateMin, float spawnRateMax, float lifeTime
		,int spawnAmount = 1 , float nextSpawn = 0.0f, float warmupTime = 0.0f, float loopTime = 0.0f, float currTime = 0.0f, unsigned int particleCap = 10);

	void AssignParticleSpawnInfo(const char* meshName, const char* textureName, ColorInfo color, AEVec2 scaleFactor
		, float totalLifeTime, AEVec2 gravity, AEVec2 direction, float velocity, float rotation, unsigned int layer);
	void AssignSpawnVariance(ColorInfo c1 = { 0 }, ColorInfo c2 = { 0 }, VARIANCETYPE colorVarType = VARIANCETYPE::NONE 
		, AEVec2 scale1 = { 0 }, AEVec2 scale2 = { 0 }, VARIANCETYPE scaleVarType = VARIANCETYPE::NONE
		, AEVec2 dir1 = { 0 }, AEVec2 dir2 = { 0 }, VARIANCETYPE dirVarType = VARIANCETYPE::NONE
		, float velocity1 = 0.0f, float velocity2 = 0.0f, VARIANCETYPE velocityVarType = VARIANCETYPE::NONE
		,float spawnRate1 = 0.0f, float spawnRate2 = 0.0f, VARIANCETYPE spawnRateVarType = VARIANCETYPE::RANDOM
		,float lifeTime1 = 0.0f, float lifeTime2 = 0.0f, VARIANCETYPE spawnLifeTimeVarType = VARIANCETYPE::NONE);
	
	~cParticleEmitter() = default;										// Virtual Destructor

	void AddOverLifetime_Color(ColorInfo colorVar);
	void AddOverLifetime_Scale(AEVec2 scaleVar);
	void AddOverLifetime_Direction(AEVec2 directionVar);
	void AddOverLifetime_Velocity(float velocityVar);
	void AddOverLifetime_Rotation(float rotation);
};
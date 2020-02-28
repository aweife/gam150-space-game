#pragma once

#include "Component.h"					//Base Class
#include "AEEngine.h"

class cParticleEmitter :public Component
{
public:
	//Data

	AEVec2 _spawnPosition = { 0, 0 };
	float _emissionRadius = 0.0f;
	float _spawnRateMin = 0.0f;
	float _spawnRateMax = 0.0f;


	// Constructor with parameter
	cParticleEmitter() = delete;
	cParticleEmitter(AEVec2 spawnPos, float radius, float spawnRateMin, float spawnRateMax);
	~cParticleEmitter();										// Virtual Destructor

};
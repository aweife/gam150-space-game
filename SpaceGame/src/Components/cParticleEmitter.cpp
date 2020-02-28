#include "cParticleEmitter.h"

cParticleEmitter::cParticleEmitter(AEVec2 spawnPos, float radius, float spawnRateMin, float spawnRateMax)
	:_spawnPosition{spawnPos}, _emissionRadius{radius}, _spawnRateMin{spawnRateMin}, _spawnRateMax{spawnRateMax}
{

}

cParticleEmitter::~cParticleEmitter()
{

}
#include "ParticleEmitterSystem.h"
#include "../ECS/Core.h"
#include "../Components/cParticleEmitter.h"
#include "../Components/cTransform.h"
#include "../Global.h"

void ParticleEmitterSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cParticleEmitter>());
	Core::Get().SetSystemSignature<ParticleEmitterSystem>(signature);
}
void ParticleEmitterSystem::Update()
{
	cTransform* transformComponent;
	cParticleEmitter* emitterComponent;
	std::set<ENTITY> markedForDestruction;

	for (auto const& entities : entitiesList)
	{
		transformComponent = Core::Get().GetComponent<cTransform>(entities);
		emitterComponent = Core::Get().GetComponent<cParticleEmitter>(entities);

		if (!emitterComponent->_isAlive)
		{
			if (emitterComponent->_recycleParticlePool.size() >= emitterComponent->_particlePool.size())
			{
				markedForDestruction.insert(entities);
			}
			continue;
		}

		//Check if next spawn
		if ((emitterComponent->_spawnRateCurr + emitterComponent->_lastSpawnTime) < g_appTime)
		{
			//Determine spawn position of particle
			AEVec2 emitterPosition = Define_ParticleSpawnPos(transformComponent->_position, emitterComponent->_spawnPositionOffset
				, emitterComponent->_emissionRadius);

			//Spawn the particles! Woohoo
			for (size_t i = 0; i < emitterComponent->_spawnAmount; ++i)
			{
				CreateParticleFromEmitter(emitterComponent, emitterPosition, entities);
			}
			
			//Calculate next spawn time
			emitterComponent->_lastSpawnTime = g_appTime;
			float loopPercent = emitterComponent->_currTime / emitterComponent->_loopTime;

			emitterComponent->_spawnRateCurr = Define_CommonFloat(emitterComponent->_spawnRateVariance[0],
				emitterComponent->_spawnRateVariance[1], emitterComponent->_spawnRateVariance[0],
				loopPercent, emitterComponent->_spawnRateVarType);
		}

		//Time update
		emitterComponent->_currTime += g_dt;
		if (emitterComponent->_currTime >= emitterComponent->_loopTime)
		{
			emitterComponent->_currTime = 0.0f;
		}
		emitterComponent->_currlifeTime += g_dt;
		if (emitterComponent->_currlifeTime > emitterComponent->_lifeTime)
		{
			emitterComponent->_isAlive = false;
		}
	}

	//Destroy particle emitters
	if (markedForDestruction.size() > 0)
	{
		for (auto const& entity : markedForDestruction)
		{
			Core::Get().EntityDestroyed(entity);
		}
		markedForDestruction.clear();
	}
}

ENTITY CreateParticleFromEmitter(cParticleEmitter* emitter, AEVec2 position, ENTITY emitterID)
{
	float curvePercentage = emitter->_currTime / emitter->_loopTime;

	ColorInfo spawnColor = DefineColor(emitter->_colorVariance[0], emitter->_colorVariance[1], emitter->_particleToSpawn._currColor
		, curvePercentage, emitter->_spawnColorVarType);
	AEVec2 spawnScale = Define_AEVEC2(emitter->_scaleVariance[0], emitter->_scaleVariance[1], emitter->_particleToSpawn._scaleFactor
		, curvePercentage, emitter->_spawnScaleVarType);
	float spawnLifeTime = Define_CommonFloat(emitter->_lifeTimeVariance[0], emitter->_lifeTimeVariance[1], emitter->_particleToSpawn._totalLifeTime
		, curvePercentage, emitter->_spawnLifeTimeVarType);
	AEVec2 spawnDirection = Define_AEVEC2(emitter->_directionVariance[0], emitter->_directionVariance[1], emitter->_particleToSpawn._direction
		, curvePercentage, emitter->_spawnDirectionVarType);
	float spawnVelocity = Define_CommonFloat(emitter->_velocityVariance[0], emitter->_velocityVariance[1], emitter->_particleToSpawn._velocityBase
		, curvePercentage, emitter->_spawnVelocityVarType);

	//Instantiate the particle to the world
	ENTITY particle;
	if (emitter->_recycleParticlePool.size() > 0)
	{
		particle = emitter->_recycleParticlePool.front();
		emitter->_recycleParticlePool.pop();
		//Reset values on the particle
		ReuseParticle(particle, position, emitter->_particleToSpawn._rotation, spawnScale, spawnColor, spawnScale, spawnLifeTime, emitter->_particleToSpawn._gravity
			,spawnDirection, spawnVelocity, emitterID, emitter->_particleToSpawn._layer);
	}
	else if(emitter->_particleCap > emitter->_particlePool.size())
	{
		particle = Core::Get().CreateEntity();
		Core::Get().AddComponent(particle, new cTransform(position, emitter->_particleToSpawn._rotation, spawnScale));
		Core::Get().AddComponent(particle, new cParticle(emitter->_spawnMeshName, emitter->_spawnTextureName,
			spawnColor, spawnScale, spawnLifeTime, emitter->_particleToSpawn._gravity, spawnDirection, spawnVelocity,
			emitterID, emitter->_particleToSpawn._rotation, emitter->_particleToSpawn._layer));
		emitter->_particlePool.push(particle);
	}
	else 
	{
		return 0;				//Reached max capacity
	}
	cParticle*  particleComponent = Core::Get().GetComponent<cParticle>(particle);

	for (auto i : emitter->_particleToSpawn._colorOverLifetime)
	{
		particleComponent->AddOverLifetime_Color(i);
	}
	for (auto i : emitter->_particleToSpawn._scaleOverLifetime)
	{
		particleComponent->AddOverLifetime_Scale(i);
	}
	for (auto i : emitter->_particleToSpawn._directionOverLifetime)
	{
		particleComponent->AddOverLifetime_Direction(i);
	}
	for (auto i : emitter->_particleToSpawn._velocityOverLifetime)
	{
		particleComponent->AddOverLifetime_Velocity(i);
	}
	for (auto i : emitter->_particleToSpawn._rotationOverLifetime)
	{
		particleComponent->AddOverLifetime_Rotation(i);
	}
	return particle;
}

ColorInfo DefineColor(ColorInfo a, ColorInfo b, ColorInfo base, float curvePercent, VARIANCETYPE variance)
{
	switch (variance)
	{
		case VARIANCETYPE::RANDOM:
			ColorInfo randomColor;
			randomColor.r = AERandFloat() * (b.r - a.r) + a.r;
			randomColor.g = AERandFloat() * (b.g - a.g) + a.g;
			randomColor.b = AERandFloat() * (b.b - a.b) + a.b;
			randomColor.a = AERandFloat() * (b.a - a.a) + a.a;
			return randomColor;

		case VARIANCETYPE::CURVE:
			ColorInfo curveColor;
			curveColor.r = ((b.r - a.r) * curvePercent) + a.r;
			curveColor.g = ((b.g - a.g) * curvePercent) + a.g;
			curveColor.b = ((b.b - a.b) * curvePercent) + a.b;
			curveColor.a = ((b.a - a.a) * curvePercent) + a.a;
			return curveColor;
	}
	return base;			//case VARIANCETYPE::NONE
}

float Define_CommonFloat(float a, float b, float base, float curvePercent, VARIANCETYPE variance)
{
	switch (variance)
	{
	case VARIANCETYPE::RANDOM:
		return (AERandFloat() * (b - a) + a);

	case VARIANCETYPE::CURVE:
		return (((b - a) * curvePercent) + a);
	}
	return base;			//case VARIANCETYPE::NONE
}

AEVec2 Define_AEVEC2(AEVec2 a, AEVec2 b, AEVec2 base, float curvePercent, VARIANCETYPE variance)
{
	AEVec2 randomVec2;
	float rand;
	switch (variance)
	{
	case VARIANCETYPE::RANDOM_UNIFORM:
		rand = AERandFloat() * (b.x - a.x) + a.x;
		AEVec2Set(&randomVec2, rand, rand);
		return randomVec2;

	case VARIANCETYPE::RANDOM:
		AEVec2Set(&randomVec2, AERandFloat() * (b.x - a.x) + a.x, AERandFloat() * (b.y - a.y) + a.y);
		return randomVec2;

	case VARIANCETYPE::CURVE:
		AEVec2 curveVec2;
		AEVec2Set(&curveVec2,((b.x - a.x) * curvePercent) + a.x, ((b.y - a.y) * curvePercent) + a.y);
		return curveVec2;
	}
	return base;			//case VARIANCETYPE::NONE
}

AEVec2 Define_ParticleSpawnPos(AEVec2 emitterPos, AEVec2 emitterOffset, float radius)
{
	AEVec2 finalPosition;
	AEVec2Add(&finalPosition, &emitterPos, &emitterOffset);

	//calculate a randomised position within radius
	//Choose angle first then choose distance
	float theta = AERandFloat() * 2 * PI;	//0 to 2PI
	float rDis = (AERandFloat() * 2 - 1) * radius;
	AEVec2 randPosition;
	AEVec2Set(&randPosition, rDis * AECos(theta), rDis * AESin(theta));

	AEVec2Add(&finalPosition, &finalPosition, &randPosition);

	return finalPosition;
}	

void ReuseParticle(ENTITY particle, AEVec2 position, float rotation, AEVec2 scale, ColorInfo spawnColor, AEVec2 spawnScale
	, float spawnLifeTime, AEVec2 gravity, AEVec2 spawnDirection, float spawnVelocity, ENTITY emitterID
	, unsigned int layer)
{
	cTransform* transformComponent = Core::Get().GetComponent<cTransform>(particle);
	cParticle* particleComponent = Core::Get().GetComponent<cParticle>(particle);

	transformComponent->_position = position;
	transformComponent->_rotation = rotation;
	transformComponent->_scale = scale;
	particleComponent->_isAlive = true;
	particleComponent->_isVisible = true;
	particleComponent->_particleData._currColor = spawnColor;
	particleComponent->_particleData._scaleFactor = spawnScale;
	particleComponent->_particleData._currLifeTime = 0.0f;
	particleComponent->_particleData._totalLifeTime = spawnLifeTime;
	particleComponent->_particleData._gravity = gravity;
	particleComponent->_particleData._currGravity.x = 0.0f;
	particleComponent->_particleData._currGravity.y = 0.0f;
	particleComponent->_particleData._direction = spawnDirection;
	particleComponent->_particleData._velocityBase = spawnVelocity;
	particleComponent->_particleData._rotation = rotation;
	particleComponent->_emitterID = emitterID;			//actually redundant
	particleComponent->_particleData._layer = layer;

	particleComponent->_particleData._colorOverLifetime.clear();
	particleComponent->_particleData._scaleOverLifetime.clear();
	particleComponent->_particleData._directionOverLifetime.clear();
	particleComponent->_particleData._velocityOverLifetime.clear();
	particleComponent->_particleData._rotationOverLifetime.clear();
}

void ParticleEmitterSystem::OnComponentRemove(ENTITY entity)
{
	cParticleEmitter* emitterComponent = Core::Get().GetComponent<cParticleEmitter>(entity);
	while (emitterComponent->_particlePool.size() > 0)
	{
		ENTITY particle = emitterComponent->_particlePool.front();
		Core::Get().EntityDestroyed(particle);					//Destroy all particles that are managed by the emitter
		emitterComponent->_particlePool.pop();
	}
}
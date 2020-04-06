/*********************************************************************************
* \file			ParticleEmitterSystem.h
* \brief		Particle Emitter System for particle creations
* \author		Chong Jun Yi, 100% Code Contribution
*
*				Emitter System allows creation of different types of Particle types.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/


#pragma once
#include "System.h"
#include "../Components/cParticle.h"		//ColorInfo
#include "../Components/cParticleEmitter.h"	//VARIANCE TYPE

class ParticleEmitterSystem :public System
{
public:
	ParticleEmitterSystem() = default;
	~ParticleEmitterSystem() = default;
	void Init() override;
	void Update() override;					
	void Render() override {};
	void OnComponentAdd(ENTITY) {};
	void OnComponentRemove(ENTITY);

};

ENTITY CreateParticleFromEmitter(cParticleEmitter* emitter, AEVec2 position, ENTITY emitterID);

ColorInfo DefineColor(ColorInfo a, ColorInfo b, ColorInfo base, float curvePercent, VARIANCETYPE variance);

float Define_CommonFloat(float a, float b, float base, float curvePercent, VARIANCETYPE variance);

AEVec2 Define_AEVEC2(AEVec2 a, AEVec2 b, AEVec2 base, float curvePercent, VARIANCETYPE variance);

AEVec2 Define_ParticleSpawnPos(AEVec2 emitterPos, AEVec2 emitterOffset, float radius);

void ReuseParticle(ENTITY particle, AEVec2 position, float rotation, AEVec2 scale, ColorInfo spawnColor, AEVec2 spawnScale
	, float spawnLifeTime, AEVec2 gravity, AEVec2 spawnDirection, float spawnVelocity, ENTITY emitterID
	, unsigned int layer);
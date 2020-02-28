#pragma once

#include "System.h"

class ParticleSystem :public System
{
public:
	//data
	std::set<ENTITY> emitterList;
	unsigned int emitterCount = 0;

	ParticleSystem() = default;
	~ParticleSystem() = default;
	void Init() override;
	void Update() override;					//Update Emitter
	void Render() override;					//Update Particless
	void OnComponentAdd(ENTITY entity);
	void OnComponentRemove(ENTITY) {};

};

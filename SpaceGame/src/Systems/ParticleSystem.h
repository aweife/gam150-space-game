/**********************************************************************************
* \file			ParticleSystem.h
* \brief		Particle System
* \author		Jun Yi, Chong, 100% Code Contribution
*
*				Long Description
*				- Update each particle
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "System.h"

class ParticleSystem :public System
{
public:
	//Order here affects sequence of set
	std::set<ENTITY> entityLayer7;	//Background
	std::set<ENTITY> entityLayer6;	//Background
	std::set<ENTITY> entityLayer5;	//Parallax3
	std::set<ENTITY> entityLayer4;	//Parallax2
	std::set<ENTITY> entityLayer3;	//Parallax1
	std::set<ENTITY> entityLayer2;	//Player
	std::set<ENTITY> entityLayer1;	//Foreground
	std::set<ENTITY> entityLayer0;	//UI

	ParticleSystem() = default;
	~ParticleSystem() = default;
	void Init() override;
	void Update() override;					//Update Emitter
	void Render() override {};					//Update Particless

	void RenderLayer(unsigned int layer, float parallaxOffX, float parallaxOffY);
	void OnComponentAdd(ENTITY entity);
	void OnComponentRemove(ENTITY entity);

};

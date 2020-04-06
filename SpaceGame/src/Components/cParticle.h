/**********************************************************************************
* \file			cParticle.h
* \brief		List of components for the engine
* \author		Jun Yi,				Chong,  100% Code Contribution
*
*				Contain data about the particle component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "Component.h"					//Base Class
#include "AEEngine.h"
#include "../Global_Graphics.h"			//ColorInfo
#include <vector>


struct ParticleInfo
{
	ColorInfo _currColor;
	AEVec2 _scaleFactor;
	float _totalLifeTime;
	float _currLifeTime;
	AEVec2 _gravity;
	AEVec2 _currGravity;
	AEVec2 _direction;
	float _velocityBase;
	float _rotation;
	unsigned int _layer;

	std::vector<ColorInfo>	_colorOverLifetime;
	std::vector<AEVec2>		_scaleOverLifetime;
	std::vector <AEVec2>	_directionOverLifetime;
	std::vector<float>		_velocityOverLifetime;
	std::vector<float>		_rotationOverLifetime;
};

class cParticle :public Component
{
public:
	//Data	
	bool _isAlive;										//Mainly for recycling particles
	bool _isVisible				= true;					//Mainly for effiencient rendering
	AEGfxVertexList* _mesh;
	AEGfxTexture* _texture;
	ParticleInfo _particleData;
	ENTITY _emitterID;

	// Constructor with parameter
	cParticle() = delete;
	cParticle(const char* meshName, const char* textureName, ColorInfo color, AEVec2 scaleFactor
		, float totalLifeTime, AEVec2 gravity, AEVec2 direction, float velocity, ENTITY emitterID, float rotation = 0, unsigned int layer = 2);
	~cParticle();										// Virtual Destructor

	void LoadMesh(const char* meshName);
	void LoadTexture(const char* textureName);

	void AddOverLifetime_Color(ColorInfo colorVar);
	void AddOverLifetime_Scale(AEVec2 scaleVar);
	void AddOverLifetime_Direction(AEVec2 directionVar);
	void AddOverLifetime_Velocity(float velocityVar);
	void AddOverLifetime_Rotation(float rotation);
};
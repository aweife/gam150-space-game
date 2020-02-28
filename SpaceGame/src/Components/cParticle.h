#pragma once

#include "Component.h"					//Base Class
#include "AEEngine.h"

struct ColorInfo
{
	float r;
	float g;
	float b;
	float a;
};

class cParticle :public Component
{
public:
	//Data
	AEGfxVertexList* _mesh;
	AEGfxTexture* _texture;
	bool isAlive;

	unsigned int _emitterID;
	ColorInfo _currColor;
	float _scaleFactor;
	float _warmUpTime;
	float _totalLifeTime;
	float _currLifeTime;
	AEVec2 _gravity;
	AEVec2 _velocityBase;

	ColorInfo _colorVariance;
	float _scaleVariance;
	AEVec2 _velocityVariance;	

	// Constructor with parameter
	cParticle() = delete;
	cParticle(const char* meshName, const char* textureName, ColorInfo color, float scaleFactor, float warmUpTime, float totalLifeTime
		, AEVec2 gravity, AEVec2 velocity, ColorInfo colorVar, float scaleVar, AEVec2 velocityVar);
	~cParticle() {};										// Virtual Destructor

	void LoadMesh(const char* meshName);
	void LoadTexture(const char* textureName);
};
#pragma once

#include "System.h"

class RenderSystem : public System
{
private:
	//Order here affects sequence of set
	std::set<ENTITY> entityLayer7;	//Static Background
	std::set<ENTITY> entityLayer6;	//Background
	std::set<ENTITY> entityLayer5;	//Parallax3
	std::set<ENTITY> entityLayer4;	//Parallax2
	std::set<ENTITY> entityLayer3;	//Parallax1
	std::set<ENTITY> entityLayer21;	//Behind player
	std::set<ENTITY> entityLayer2;	//Player
	std::set<ENTITY> entityLayer1;	//Foreground
	std::set<ENTITY> entityLayer0;	//UI

	std::set<std::set<ENTITY>*> allLayer = 
	{
		&entityLayer7, &entityLayer6, &entityLayer5, &entityLayer4, &entityLayer3, &entityLayer21, &entityLayer2, &entityLayer1, &entityLayer0,
	};

public:
	RenderSystem() = default;
	~RenderSystem() = default;
	void Init() override;
	void Update() override {};
	void Render() override;
	void OnComponentAdd(ENTITY entity);
	void OnComponentRemove(ENTITY entity);
};

namespace RenderingTricks
{
	void LightSpeedEffectOut(ENTITY target, float elapsedTime, int counter,
		float increment, float alphaDecrement, float degree);

	void LightSpeedEffectIn(ENTITY target, float elapsedTime, float totalTime, float timeOffset, int counter,
		float maxRangeX, float maxRangeY, float desiredX, float desiredY, float alphaIncrement, float degree);
}
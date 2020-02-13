#pragma once

#include "System.h"

class RenderSystem : public System
{
private:
	std::set<ENTITY> entityLayer6;	//Background
	std::set<ENTITY> entityLayer5;	//Parallax3
	std::set<ENTITY> entityLayer4;	//Parallax2
	std::set<ENTITY> entityLayer3;	//Parallax1
	std::set<ENTITY> entityLayer2;	//Player
	std::set<ENTITY> entityLayer1;	//Foreground
	std::set<ENTITY> entityLayer0;	//UI

	std::set<std::set<ENTITY>*> allLayer = 
	{
		&entityLayer6,
		&entityLayer5,
		&entityLayer4,
		&entityLayer3,
		&entityLayer2,
		&entityLayer1,
		&entityLayer0,
	};

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void OnComponentAdd(ENTITY entity);
	void OnComponentRemove(ENTITY entity);
};
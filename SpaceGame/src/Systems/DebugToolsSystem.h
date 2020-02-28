#pragma once

#include "System.h"

class DebugToolsSystem :public System
{

public:
	DebugToolsSystem() = default;
	~DebugToolsSystem() = default;
	void Init() override;								//Define System signature
	void Update() override {};							
	void Render() override;								//Render debug lines on screen
	void OnComponentAdd(ENTITY) {};
	void OnComponentRemove(ENTITY) {};

};
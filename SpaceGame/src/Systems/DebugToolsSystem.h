/*********************************************************************************
* \file			DebugToolsSystem.h
* \brief		Debugging tool to assist in debug
* \author		Chong Jun Yi, 100% Code Contribution
*
*				Debugging tool to assist in debug
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once
#include "System.h"

class DebugToolsSystem :public System
{

public:
	std::set<ENTITY> meshOutlineList;

	DebugToolsSystem() = default;
	~DebugToolsSystem() = default;
	void Init() override;								//Define System signature
	void Update() override {};							
	void Render() override;								//Render debug lines on screen
	void OnComponentAdd(ENTITY) {};
	void OnComponentRemove(ENTITY) {};
};	

void ShowAll_BoundingBoxOutline();
void RemoveAll_BoundingBoxOutline();
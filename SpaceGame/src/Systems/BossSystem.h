/*********************************************************************************
* \file			BossSystem.h
* \brief		Logic for the Final Boss
* \author		Ang Wei Feng, 100% Code Contribution
*
*				Logic for the Final Boss
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once

#include "System.h"

#include "../AI/aiBlackBoard.h"


class BossSystem : public System
{
public:
	BossSystem() = default;
	~BossSystem() = default;
	void Init() override;
	void Render() override {};
	void Update() override;
	void OnComponentAdd(ENTITY) override;
	void OnComponentRemove(ENTITY) override;

private:
	void CheckOutOfScreen(ENTITY id);
};
/**********************************************************************************
* \file			objEnter.h
* \brief		AI enter state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise enter state of AI
*				- Treat an objective like an inactive ai
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"

class objEnter : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	// Extra components this state needs

	// State variables
	float _stayDuration;
	float _stayTimer;
};

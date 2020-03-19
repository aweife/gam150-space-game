/**********************************************************************************
* \file			aiChase.h
* \brief		??
* \author		Wei Feng, Ang, 100% Code Contribution
*
*				Long Description
*				- 
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"
#include "../../Components/cTransform.h"
#include "../../Components/cRigidBody.h"

class aiChase : public aiBase
{
public:
	virtual void Run(aiBlackBoard&, aiStateList&) override;
private:

	// Component this state needs
	cTransform* trans;
	cRigidBody* rb;

	float _chaseTimer;
};

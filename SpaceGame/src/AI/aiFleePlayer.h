#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"

class aiFleePlayer : public aiBase
{
public:
	virtual void Run( const aiBlackBoard&, the_variant& ) override;
private:
	cTransform* trans;
	cRigidBody* rb;
};
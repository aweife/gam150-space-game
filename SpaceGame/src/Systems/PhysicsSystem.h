#pragma once

#include "../Global.h"
#include "../Components/Component.h"
#include "System.h"
#include "../Components/RigidBodyComponent.h"

/**************************************************************************/
/*!
	This is the struct for the AABB collision detection
	*/
/**************************************************************************/

struct AABB
{
	//AEVec2	c; // center
	//float  r[2]; // holds half width and half height

	Vector2D	min;
	Vector2D	max;
};

class PhysicsSystem : public System
{
public: 
	void Init(RigidBodyComponent body);

	void Update();
};


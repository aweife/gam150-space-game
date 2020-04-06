/*********************************************************************************
* \file			cCollision.cpp
* \brief		Camera Component
* \author		Farzaana Binte,		Roslan,		100% Code Contribution
*
*				Responsible for Collision component
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"
#include "AEEngine.h"

/**************************************************************************/
/*!
	This is the struct for the AABB collision detection
*/
/**************************************************************************/
struct Colliders
{
	AEVec2	center;      // center
	AEVec2  rad;
	float   radius;       // holds half width and half height

	AEVec2	min;
	AEVec2	max;
	AEVec2  _point;
};

// To check which shapes is used for the game object 
enum class ColliderShape
{
	CIRCLE = 0,
	RECTANGLE = 1,
	RECTANGLE_OBB = 2,
	RAYCAST = 3,
	NONE
};

class cCollision:public Component
{

public:
	//Game object instance structure
	unsigned long		_flag			= 0;						// bit _flag or-ed together
	Colliders		    _boundingBox		= { 0 };				// object bouding box that encapsulates the object
	ColliderShape		_bbShape			= ColliderShape::NONE;

	// Constructor
	cCollision() = default;

	// Destructor
	~cCollision() = default;

};
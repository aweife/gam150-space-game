/*********************************************************************************
* \file			cCollision.h
* \author		Farzaana Binte Roslan
* \version		1.0
* \date			31/01/2020
* \par			Systems
* \note			Course: GAM150
* \brief		Collision component that handles the collision between two
				objects

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
struct AABB
{
	AEVec2	center;      // center
	AEVec2  rad;
	float   radius;       // holds half width and half height

	AEVec2	min;
	AEVec2	max;
};

// To check which shapes is used for the game object 
enum class ColliderShape
{
	CIRCLE = 0,
	RECTANGLE = 1,
	NONE
};

class cCollision:public Component
{

public:
	//Game object instance structure
	unsigned long		_flag			= 0;						// bit _flag or-ed together
	AABB				_boundingBox		= { 0 };				// object bouding box that encapsulates the object
	ColliderShape		_bbShape			= ColliderShape::NONE;

	// Constructor
	cCollision() = default;

	// Destructor
	~cCollision() = default;

	//// Checking for Collision (Circle)
	//bool checkforCollisionCircle();

};
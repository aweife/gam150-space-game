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

#include "AEEngine.h"

/**************************************************************************/
/*!
	This is the struct for the AABB collision detection
	*/
/**************************************************************************/
struct AABB
{
	//AEVec2	c; // center
	//float  r[2]; // holds half width and half height

	AEVec2	min;
	AEVec2	max;
};


class cCollision
{

public:
	//Game object instance structure
	unsigned long		flag;		// bit flag or-ed together
	AABB				boundingBox;// object bouding box that encapsulates the object
	const char*			name = "";
	// Constructor
	cCollision() = default;

	// Destructor
	~cCollision() = default;

	//// Checking for Collision (Circle)
	//bool checkforCollisionCircle();

};
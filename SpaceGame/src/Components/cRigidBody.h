#pragma once

#include "AEEngine.h"

class cRigidBody
{
public:
	float mass;                              // Mass of the ship
	float inertia;                           // Inertia
	float inertiaInverse;                    // Inverse Inertia
	AEVec2 _position;						 // Position of the spaceship
	AEVec2 velocity;						 // Velocity of the ship
	AEVec2 angularVelocity;					 // Angular Velocity of the ship (not sure if needed)

	// Constructor
	cRigidBody();

	// Destructor
	~cRigidBody() = default;
};
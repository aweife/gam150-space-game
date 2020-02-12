#pragma once

#include "AEEngine.h"

struct RigidBodyComponent
{
	float mass;                              // Mass of the ship
	float inertia;                           // Inertia
	float inertiaInverse;                    // Inverse Inertia
	AEVec2 position;						 // Position of the spaceship
	AEVec2 velocity;						 // Velocity of the ship
	AEVec2 angularVelocity;					 // Angular Velocity of the ship (not sure if needed)

	// Constructor
	RigidBodyComponent();

	// Destructor
	~RigidBodyComponent() = default;
};
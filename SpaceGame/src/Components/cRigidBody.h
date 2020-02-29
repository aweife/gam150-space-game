#pragma once

#include "AEEngine.h"

enum class COLLISIONTAG
{
	PLAYER = 0, 
	BULLET = 1,
	ENEMY = 2,
	PLANET = 3
};

class cRigidBody
{
public:
	float _mass;                              // Mass of the object
	float _velocity;                          // Velocity Value of the ship
	float _velocityCap;                       // Velocity Value of the ship
	float _acceleration;					  // Acceleration
	float _rotateVelocity;					  // How fast the ship rotate

	AEVec2 _velocityVector;					  // The current velocity since the last frame (updated by the physics system )
	AEVec2 _velocityChangeVector;             // Velocity change in the current frame (before physics system)
	AEVec2 _velocityDirection;                // Mainly for normalised Direction at the end of the physics system 
	AEVec2 _angularVelocity;				  // Vector towards rotation direction

	COLLISIONTAG tag;

	// Constructor
	cRigidBody() = delete;
	cRigidBody(float mass, float velocity,
		float velocityCap = 0.0f, float acceleration = 0.0f,
		float rotateVelocity = 0.0f);


	float calculateVelwithAcc(float velocity);

	// Destructor
	~cRigidBody() = default;
};
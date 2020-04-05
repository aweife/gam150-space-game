#pragma once

#include "Component.h"
#include "AEEngine.h"

enum class OWNERTAG
{
	PLAYER = 0,
	AI = 1,
};

enum class COLLISIONTAG
{
	NONE = 0,
	PLAYER, 
	PLAYER_MENU,
	BULLET,
	BULLET_PLAYER,
	ENEMY,
	BOSS,
	PLANET,
	PLANET_ASTEROID,
	OBJECTIVE,
	MENU_BEGIN, MENU_OPTIONS, MENU_CREDITS, MENU_QUIT, MENU_BACK
};

class cRigidBody:public Component
{
public:
	float _mass;
	float _velocity;                          // Velocity Value of the ship
	float _velocityCap;                       // Max velocity Value of the ship
	float _velocitySoftCap;                   // Main velocity cap
	float _velocityHardCap;                   // Secondary Mode for boosting speed
	float _acceleration;					  // Acceleration
	float _rotateVelocity;					  // How fast the ship rotate
	float _airResistance = 0.999f;

	AEVec2 _velocityVector;					  // The current velocity since the last frame (updated by the physics system)
	AEVec2 _velocityChangeVector;             // Velocity change in the current frame (before physics system) 
	AEVec2 _velocityDirection;                // Mainly for normalised Direction at the end of the physics system 
	AEVec2 _angularVelocity;				  // Vector towards rotation direction
	AEVec2 _gravityVelocity;                  // Vector that handles the gravity
	AEVec2 _steeringVector;					  // Target direction that the Ai wants to travel
	AEVec2 _collisionVector;                  // Vector that forces the object to move in that direction when collided
	AEVec2 _rotationVector;                   // Rotation vector to rotate the planet.

	COLLISIONTAG _tag;						  // Indicate what objects are colliding

	// Constructor
	cRigidBody() = delete;
	cRigidBody(float mass, float velocity, float velocityCap = 2.0f, float baseAcceleration = 0.0f,
		float rotateVelocity = 0.0f, COLLISIONTAG tag = COLLISIONTAG::NONE);
	// Destructor
	~cRigidBody() = default;

	// Helper Functions
	float CalculateVelwithAcc(float velocity);
};
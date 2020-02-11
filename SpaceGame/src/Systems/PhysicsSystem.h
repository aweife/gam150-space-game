#pragma once

#include "../Global.h"
#include "../Components/Component.h"

/*
// Collision
class Collider
{

};

class Gravity
{
protected:
	float force;
	// other common things here


	// pseudo gravity

	// orbital gravity

};

class PseudoGravity:public Gravity
{

};

class OrbitalGravity :public Gravity
{

};
*/

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

class RigidBodyComponent : public Component
{
	float mass;                              // Mass of the ship
	float inertia;                           // Inertia
	float inertiaInverse;                    // Inverse Inertia
	Vector2D position;						 // Position of the spaceship
	Vector2D velocity;                       // Velocity of the ship
	Vector2D angularVelocity;                // Angular Velocity of the ship (not sure if needed)
	

public: 
	// Constructor
	RigidBodyComponent();

	// Destructor
	~RigidBodyComponent() = default;

	// Getters 
	float getMass();
	float getInertia();
	float getInertiaInverse();
	Vector2D getPosition();
	Vector2D getVelocity();
	Vector2D getAngularVelocity();

	void Initialize(RigidBodyComponent body);
	void Update();
};

class CollisionComponent : public Component
{

public: 
	// Constructor
	CollisionComponent();

	// Destructor
	~CollisionComponent();

	// Checking for Collision (AABB)
	bool checkforCollisionAABB(const AABB & obj1, const Vector2D & vel1,
		                       const AABB & obj2, const Vector2D & vel2);

	// Checking for Collision (Circle)
	bool checkforCollisionCircle();
};
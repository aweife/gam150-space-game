#pragma once



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
	float _velocity;
	float _acceleration;
	// float _mass;

public: 
	// Constructor
	RigidBodyComponent();

	// Destructor
	~RigidBodyComponent();

	// Getters 
	float getVelocity();
	float getAcceleration();
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
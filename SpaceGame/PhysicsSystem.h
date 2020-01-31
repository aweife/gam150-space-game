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

// Velocity - can use vector 2 
class Velocity
{
	struct 
	{
		float x; 
		float y;
	}Vector2D;


	float deltatime; 
	float distance;
public: 
	//Velocity() : deltatime{ deltatime }, distance{distance};
	// Using default destructor

	// To compute velocity
	float VelocityComputation(float deltatime, float xPos, float yPos);



};

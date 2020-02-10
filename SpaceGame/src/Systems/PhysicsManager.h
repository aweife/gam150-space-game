#pragma once
#include <vector>
#include "../GameObjects/GameObject.h"


class PhysicsManager
{
private:
	/* Here will be the instance stored. */
	static PhysicsManager* instance;
	std::vector<GameObject> gObjList;
	short gObjCount;

	/* Private constructor to prevent instancing. */
	PhysicsManager();

public:
	float VelocityInit();
	float VelocityUpdate();

	//Store objs and update objects
	bool CollisionDetectionAABB();
};


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
//class Velocity
//{
//	
//public: 
//
//	 
//
//
//
//};

#include <cmath>
#include "Physics.h"

float Physics::VelocityComputation(float deltatime, float x1, float y1, float x2, float y2)
{
	// v = (change of distance)/ deltatime

	float changeofDistance = 0;
	float changeinX = (x2 - x1) * (x2 - x1);
	float changeinY = (y2 - y1) * (y2 - y1);
	changeofDistance = sqrt(changeinX + changeinY);
	float dt = deltatime;
	float Velocity = changeofDistance / dt;

	return Velocity;
}

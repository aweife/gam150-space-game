#include "PathFindingSystem.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"
#include "AEEngine.h"

void Normalize(AEVec2* result, AEVec2* vector)
{
	if (vector->x < FLT_EPSILON && vector->x > -FLT_EPSILON &&
		vector->y < FLT_EPSILON && vector->y > -FLT_EPSILON)
	{
		result->x = 0.0f;
		result->y = 0.0f;
	}
}

void Seek(AEVec2* selfPos, AEVec2* targetPos, AEVec2* selfDir)
{
	// Get vector to target direction (target - self)
	AEVec2 targetDir;
	AEVec2Sub(&targetDir, targetPos, selfPos);
	//AEVec2Normalize(&targetDir, &targetDir);

	// Get vector of steer direction
	AEVec2 steerDir;
	AEVec2Sub(&steerDir, &targetDir, selfDir);
	//AEVec2Normalize(&steerDir, &steerDir);

	// Add to current velocity vector
	AEVec2Add(selfDir, selfDir, &steerDir);
}

void Flee(AEVec2* selfPos, AEVec2* targetPos, AEVec2* selfDir)
{
	// Get vector to target direction (target - self)
	AEVec2 targetDir;
	AEVec2Sub(&targetDir, selfPos, targetPos);
	//AEVec2Normalize(&targetDir, &targetDir);

	// Get vector of steer direction
	AEVec2 steerDir;
	AEVec2Sub(&steerDir, &targetDir, selfDir);
	//AEVec2Normalize(&steerDir, &steerDir);

	// Add to current velocity vector
	AEVec2Add(selfDir, selfDir, &steerDir);
}

void PathFindingSystem::Init() 
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cPathFinding>());
	Core::Get().SetSystemSignature<PathFindingSystem>(signature);
}

void PathFindingSystem::Update() 
{
	cTransform* trans;
	cRigidBody* rb;
	cPathFinding* path;

	cTransform* targetTrans;
	//cRigidBody* targetRb;

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		trans = Core::Get().GetComponent<cTransform>(entity);
		rb = Core::Get().GetComponent<cRigidBody>(entity);
		path = Core::Get().GetComponent<cPathFinding>(entity);

		// Get target
		targetTrans = Core::Get().GetComponent<cTransform>(path->target);
		//targetRb = Core::Get().GetComponent<cRigidBody>(path->target);

		// Decide logic
		switch (path->currentState)
		{
		case PATH_SEEK:
			Seek(&trans->position, &targetTrans->position, &rb->velocityVector);
			break;
		case PATH_FLEE:
			Flee(&trans->position, &targetTrans->position, &rb->velocityVector);
			break;
		}
	}
}

void PathFindingSystem::Render() {}

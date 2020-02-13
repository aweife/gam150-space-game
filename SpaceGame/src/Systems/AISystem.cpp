#include "AISystem.h"
#include "../ECS/Core.h"
#include "../Components/ComponentList.h"

void AISystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRigidBody>());
	signature.set(Core::Get().GetComponentType<cPathFinding>());
	signature.set(Core::Get().GetComponentType<cAI>());
	Core::Get().SetSystemSignature<AISystem>(signature);
}
float timer = 0.0f;
bool shouldUpdate = false;
void AISystem::Update()
{
	timer += g_dt;
	if (timer > 1.0f)
	{
		timer = 0.0f;
		shouldUpdate = true;
	}

	if (!shouldUpdate)
		return; 

	cTransform* trans;
	cRigidBody* rb;
	cPathFinding* path;
	cAI* ai;

	cTransform* targetTrans;
	cRigidBody* targetRb;

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		trans = Core::Get().GetComponent<cTransform>(entity);
		rb = Core::Get().GetComponent<cRigidBody>(entity);
		ai = Core::Get().GetComponent<cAI>(entity);
		path = Core::Get().GetComponent<cPathFinding>(entity);

		// Get target
		targetTrans = Core::Get().GetComponent<cTransform>(path->target);
		targetRb = Core::Get().GetComponent<cRigidBody>(path->target);

		float distanceToPlayer = AEVec2Distance(&trans->position, &targetTrans->position);

		// If too close to player
		if (distanceToPlayer < ai->minDistance)
		{
			path->currentState = PATH_FLEE;
			rb->velocity = targetRb->velocity;
		}
		else if (distanceToPlayer > ai->maxDistance)
		{
			path->currentState = PATH_SEEK;
			rb->velocity = targetRb->velocity;
		}
		else
		{
			printf("ATTACKING PLAYER");
		}

		/*if can - move - away - from - player
			AND(damage - taken > morale
				OR too - close - to - player)
			move - away - from - player
		else if can - move - toward - player
			AND damage - taken < morale
			AND too - far - from - player
			move - toward - player
		else if can - attack - player
			attack - player
		else stand - still*/

		shouldUpdate = false;
	}
}

void AISystem::Render() {}
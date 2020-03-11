#include "aiState.h"
#include "../ECS/Core.h"
#include "../Math/Math.h"
#include "../Global.h"
#include "../Tools/Console.h"

void aiAttack::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);

		// Initialise state
		rotationSpeed = 10.0f;
		attackCooldownTimer = 0.0f;
		attackCooldown = 3.0f;
		numberOfAttacks = 2;
		attacksLeft = 0;
		delayBetweenAttacks = 0.5f;
		delayTimer = 0.0f;

		maxDistance = 700.0f;
		minDistance = 200.0f;

		// Change inner state
		innerState = INNER_STATE_ONUPDATE;

		break;
	case INNER_STATE_ONUPDATE:

		// Always aim at player in this state
		AimAtTarget(bb);

		// Attack with timer
		if (TargetInRange(bb))
		{
			Attack();

			// If too close to player
			if (bb.distanceFromPlayer < minDistance)
			{
				// Change inner state
				innerState = INNER_STATE_ONEXIT;

				// Change state to seek
				var.m_Varient.emplace<aiRetreat>();
			}
		}
		else
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;

			// Change state to seek
			var.m_Varient.emplace<aiChase>();
		}


		break;
	case INNER_STATE_ONEXIT:

		Console_Cout("did it go here and how many times?\n");

		break;
	}
}

void aiAttack::AimAtTarget(const aiBlackBoard& bb)
{
	trans->_rotation = 
		Transform::RotateToTarget(bb.directionToPlayerN, trans->_rotation, rotationSpeed * g_dt);
}

bool aiAttack::TargetInRange(const aiBlackBoard& bb)
{
	// If player is still in range
	return (bb.distanceFromPlayer < maxDistance);
}

void aiAttack::Attack()
{
	// Decrement timer if on cooldown
	if (attackCooldownTimer > 0.0f)
	{
		attackCooldownTimer -= g_dt;

		if (attacksLeft > 0)
		{
			// Currently attacking, set delay between attacks
			if (delayTimer > 0.0f)
				delayTimer -= g_dt;
			else
			{
				// Set delay
				delayTimer = delayBetweenAttacks;

				// Fire
				FireProjectile();
				--attacksLeft;
			}
		}
	}
	else
	{
		// Set cooldown
		attackCooldownTimer = attackCooldown;
		attacksLeft = numberOfAttacks;
	}
}

void aiAttack::FireProjectile()
{
	Console_Cout("fire");
}

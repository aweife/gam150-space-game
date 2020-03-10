#pragma once

#include "aiBase.h"
#include "../Components/cTransform.h"
#include "../Components/cRigidBody.h"

class aiAttack : public aiBase
{
public:
	virtual void Run(const aiBlackBoard&, the_variant&) override;
private:
	cTransform* trans;

	// Attack
	float rotationSpeed;
	float attackCooldownTimer;
	float attackCooldown;
	int numberOfAttacks;
	int attacksLeft;
	float delayBetweenAttacks;
	float delayTimer;

	// State transition checks
	float minDistance;
	float maxDistance;

	void AimAtTarget(const aiBlackBoard&);
	bool TargetInRange(const aiBlackBoard&);
	void Attack();
	void FireProjectile();
};
#include "../aiState.h"

#include "../../ECS/Core.h"
#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"
#include "../../Player/PlayerManager.h"

void aiPursuit::Run(aiBlackBoard& bb, aiStateList& var)
{
	

	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		// Cache player
		ptrans = Core::Get().GetComponent<cTransform>(PlayerManager::player);
		prb = Core::Get().GetComponent<cRigidBody>(PlayerManager::player);

		_pursuitTimer = 0.0f;

		// Change inner state
		innerState = INNER_STATE_ONUPDATE;
		printf("AI is pursuit\n");

		break;
	case INNER_STATE_ONUPDATE:

		_pursuitTimer += g_dt;
		_positionPrediction = _pursuitTimer / 2.0f;
		if (_positionPrediction > prb->_velocity)
		{
			_pursuitTimer = 0.0f;
			_positionPrediction = prb->_velocity;
		}
		rb->_velocity += bb.acceleration;
		Steering::Pursuit(rb->_steeringVector, _futureTargetPosition, _positionPrediction, ptrans->_position, prb->_velocityVector, trans->_position, rb->_velocity * g_dt, rb->_velocityVector);
		Steering::Wander(rb->_steeringVector, rb->_velocityDirection, bb.wanderAngle, 0.5f);

		// Look at target pos
		Transform::RotateToTarget(trans->_rotation, _futureTargetPosition, bb.rotationSpeed * g_dt);

		// Check close enough to attack or not
		AEVec2Sub(&_targetPosition, &_futureTargetPosition, &trans->_position);
		_distanceFromTarget = AEVec2Length(&_targetPosition);

		// If close enough to attack
		if (_distanceFromTarget < bb.attackRange)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;
			var.states.emplace<aiAttack>();
		}

		break;
	case INNER_STATE_ONEXIT:


		break;
	}
}

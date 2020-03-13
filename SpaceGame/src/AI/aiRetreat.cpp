#include "aiState.h"
#include "../ECS/Core.h"
#include "../Tools/Editor.h"
#include "../Global.h"

void aiRetreat::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		// Initialize state
		_safeDistance = 800.0f;
		rotationSpeed = 10.0f;
		wanderAngle = 0.0f;
		FindSafePosition(bb);


		// Change inner state
		innerState = INNER_STATE_ONUPDATE;
		printf("AI is retreating\n");

		break;
	case INNER_STATE_ONUPDATE:

		Editor_TrackVariable("safe x", _targetPosition.x);
		Editor_TrackVariable("safe y", _targetPosition.y);

		if (AEVec2Distance(&_targetPosition, &trans->_position) > 20.0f)
		{
			rb->_velocity += rb->_acceleration;
			Steering::SeekTarget(rb->_steeringVector, trans->_position, _targetPosition, rb->_velocity * g_dt, rb->_velocityVector);
			Steering::Wander(rb->_steeringVector, rb->_velocityDirection, 1.0f, rotationSpeed, wanderAngle, 2.0f);
			Transform::RotateToTarget(trans->_rotation, trans->_position, _targetPosition, rotationSpeed * g_dt);
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



		break;
	}
}

void aiRetreat::FindSafePosition(const aiBlackBoard& bb)
{
	AEVec2 desired = bb.directionToPlayerN;
	AEVec2Neg(&desired, &desired);
	AEVec2Scale(&desired, &desired, _safeDistance);
	AEVec2Add(&_targetPosition, &trans->_position, &desired);
	//AEVec2Set(&_targetPosition, -400.0f, 50.0f);
}

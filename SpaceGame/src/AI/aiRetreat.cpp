#include "aiState.h"
#include "../ECS/Core.h"
#include "../Tools/Editor.h"

void aiRetreat::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		// Initialize state
		_safeDistance = 600.0f;
		FindSafePosition(bb);


		// Change inner state
		innerState = INNER_STATE_ONUPDATE;

		break;
	case INNER_STATE_ONUPDATE:

		if(bb.distanceFromPlayer < _safeDistance)
			Flee();
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
	AEVec2Scale(&desired, &desired, _safeDistance);
	AEVec2Add(&_targetPosition, &trans->_position, &desired);
	Editor_TrackVariable("safe x", _targetPosition.x);
	Editor_TrackVariable("safe y", _targetPosition.y);
}

void aiRetreat::Flee()
{
	return;
	AEVec2 desired;
	AEVec2Sub(&desired, &_targetPosition, &trans->_position);

	// Replace with steeringVector in rb
	AEVec2 steering;
	AEVec2Sub(&steering, &desired, &rb->_velocityVector);

	// Flee
	rb->_velocityVector.x += steering.x;
	rb->_velocityVector.y += steering.y;
}

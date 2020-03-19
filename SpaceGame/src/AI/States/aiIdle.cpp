#include "../aiState.h"

#include "../../ECS/Core.h"
#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void aiIdle::Run(aiBlackBoard& bb, aiStateList& var)
{
	UNREFERENCED_PARAMETER(var);
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		break;
	case INNER_STATE_ONUPDATE:

		break;
	case INNER_STATE_ONEXIT:


		break;
	}
}

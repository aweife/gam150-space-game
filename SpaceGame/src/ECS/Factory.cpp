#include "Factory.h"
#include "Core.h"
#include "../Components/ComponentList.h"

extern Core coreInstance;

namespace Factory
{
	ENTITY CreateCamera()
	{
		ENTITY cameraID = coreInstance.CreateEntity();
		coreInstance.AddComponent<cTransform>(cameraID, new cTransform());
		coreInstance.AddComponent<cCamera>(cameraID, new cCamera());

		return cameraID;
	}
}
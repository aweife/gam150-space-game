#include "Factory.h"
#include "Core.h"
#include "../Components/ComponentList.h"

namespace Factory
{
	ENTITY CreateCamera()
	{
		ENTITY cameraID = Core::Get().CreateEntity();
		Core::Get().AddComponent<cTransform>(cameraID, new cTransform());
		Core::Get().AddComponent<cCamera>(cameraID, new cCamera());

		return cameraID;
	}
}
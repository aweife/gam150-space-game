#include "HealthSystem.h"
#include "../ECS/Core.h"
#include "../Components/cHealth.h"

void HealthSystem::Init()
{
	// Sets the system signature for this system
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cHealth>());
	Core::Get().SetSystemSignature<HealthSystem>(signature);

}

void HealthSystem::Update()
{

}
#include "ScannerSystem.h"
#include "../ECS/Core.h"
#include "../Components/cScanner.h"
#include "../Components/cTransform.h"

void ScannerSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cScanner>());
	Core::Get().SetSystemSignature<ScannerSystem>(signature);
}

void ScannerSystem::Update()
{
	cScanner* scannerComp;
	cTransform* transform;
	for (auto const& entity : entitiesList)
	{
		scannerComp = Core::Get().GetComponent<cScanner>(entity);
		transform = Core::Get().GetComponent<cTransform>(entity);

	}
}
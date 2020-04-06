/**********************************************************************************
* \file			WarpingSystem.cpp
* \brief		Handles wrapping on screen
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Handles wrapping around screen coords
*				- mostly for menu
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "WarpingSystem.h"
#include "../ECS/Core.h"
#include "../Components/cWarping.h"
#include "../Components/cTransform.h"

void WarpingSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cWarping>());
	Core::Get().SetSystemSignature<WarpingSystem>(signature);
}

void WarpingSystem::Update()
{
	cWarping* warpingComp;
	cTransform* transform;
	for (auto const& entity : entitiesList)
	{
		warpingComp = Core::Get().GetComponent<cWarping>(entity);
		transform = Core::Get().GetComponent<cTransform>(entity);

		transform->_position.x = AEWrap(transform->_position.x, warpingComp->_warpX.x, warpingComp->_warpX.y);
		transform->_position.y = AEWrap(transform->_position.y, warpingComp->_warpY.x, warpingComp->_warpY.y);

	}
}
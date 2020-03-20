#include "BossSystem.h"							//Self Header
#include "../ECS/Core.h"						//Work with ECS
#include "../Components/ComponentList.h"		//Get necessary component references
#include "../Global.h"
#include <variant>
#include "../ECS/Factory.h"
#include "UISystem.h"							//Spawn Ai Indicators
#include "../Player/PlayerManager.h"			// Update ai on player

void BossSystem::Init()
{
	SIGNATURE signature;

	//Set the bits for necessary components
	signature.set(Core::Get().GetComponentType<cBoss>());

	//Assign the signature for this System
	Core::Get().SetSystemSignature<BossSystem>(signature);
}

void BossSystem::Update()
{
	cBoss* ai;

	const ENTITY pid = PlayerManager::player;
	if (pid == 0)	return;				//NO ACTIVE PLAYER

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		ai = Core::Get().GetComponent<cBoss>(entity);

		// Update this ai's blackboard
		ai->_blackboard.UpdateBlackboard(entity);

		// Run this ai's current state
		std::visit([&](auto& state)
			{
				state.Run(ai->_blackboard, ai->_currentAttack);
			}, ai->_currentAttack.attacks);

		CheckOutOfScreen(entity);
	}
}

void BossSystem::OnComponentAdd(ENTITY) {};
void BossSystem::OnComponentRemove(ENTITY) {};

void BossSystem::CheckOutOfScreen(ENTITY id)
{
	cTransform* self = Core::Get().GetComponent<cTransform>(id);

	AEVec2 cameraPosition = { 0 };
	AEGfxGetCamPosition(&cameraPosition.x, &cameraPosition.y);

	if (!(self->_position.x > cameraPosition.x - g_WorldMaxX && self->_position.x < cameraPosition.x + g_WorldMaxX
		&& self->_position.y > cameraPosition.y - g_WorldMaxY && self->_position.y < cameraPosition.y + g_WorldMaxY))
	{
		AEVec2 relativeDirection;
		AEVec2Sub(&relativeDirection, &self->_position, &cameraPosition);
		std::shared_ptr<UISystem> uiSys(std::static_pointer_cast<UISystem>(Core::Get().GetSystem<UISystem>()));

		//@TED later just change the last variable for different enemy type
		uiSys->Check_AIIndicatorExist(id, relativeDirection, 0); //Under UI System
	}
}

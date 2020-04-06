/*********************************************************************************
* \file			WeaponSystemMelee.cpp
* \brief		Handles the melee weapon of every entities
* \author		Chong Jin Kiat, 100% Code Contribution
*
*				This system loops through all melee components in the game 
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "WeaponSystemMelee.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"							//delta time
#include "../Components/cTransform.h"
#include "../Components/cWeapon.h"

#include "../ECS/Factory.h"
/******************************************************************************/
/*!
	Global Variables
*/
/******************************************************************************/

void WeaponSystemMelee::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cMeleeWeapon>());
	Core::Get().SetSystemSignature<WeaponSystemMelee>(signature);
}

void WeaponSystemMelee::Update()
{
	cTransform* transform;
	cMeleeWeapon* meleeweapon;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		meleeweapon = Core::Get().GetComponent<cMeleeWeapon>(entity);

		//Time update
	}
}


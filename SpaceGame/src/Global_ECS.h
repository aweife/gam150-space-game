/**********************************************************************************
* \file			Global_ECS.h
* \brief		Stores global variables/allias about the ECS architechure
* \author		Jun Yi,			Chong,		100% Code Contribution
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#pragma once
#include <cstdint>
#include <bitset>

//ENTITY
typedef unsigned int ENTITY;					// ID for each entity, components will be tagged to an ID
const ENTITY MAX_ENTITIES = 500;				// Maximum number of entity in game

//COMPONENT
typedef unsigned short ComponentType;			// ID for component
const ComponentType MAX_COMPONENTS = 32;		// Maximum number of components that can be added to a entity

//ENTITY-COMPONENT
typedef std::bitset<MAX_COMPONENTS> SIGNATURE;	//A collections of bits to represent active components in an entity

enum COMPONENTID								//ID for each component, to be used to organise systems and map an entity
{
	ID_NullComponent = 0,
	ID_TransformComponent,
	ID_SpriteComponent, 
	ID_RigidBodyComponent, 
	ID_CollisionComponent,
	ID_CameraComponent,
	ID_PathFindingComponent,
	ID_AIComponent,
	ID_BossComponent,
	ID_SpaceShip,
	ID_RangeWeaponComponent,
	ID_MeleeWeaponComponent,
	ID_HealthComponent,
	ID_ProjectileComponent,
	ID_UIComponent,
	ID_DebugToolsComponent,
	ID_ParticleComponent,
	ID_ParticleEmitterComponent,
	ID_TimelineComponent,
	ID_WarpingComponent
};					


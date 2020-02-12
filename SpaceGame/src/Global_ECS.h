/*********************************************************************************
* \file			Global_ECS.h
* \author		Chong Jun Yi
* \version		1.0
* \date			30/01/2019
* \par			Data storage Code
* \note			Course: GAM150
* \brief		Stores global variables/allias about the ECS architechure
				- 
				-

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include <cstdint>
#include <bitset>

//ENTITY
typedef unsigned int ENTITY;					// ID for each entity, components will be tagged to an ID
const ENTITY MAX_ENTITIES = 1000;				// Maximum number of entity in game

//COMPONENT
typedef unsigned short ComponentType;					// ID for component
const ComponentType MAX_COMPONENTS = 32;		// Maximum number of components that can be added to a entity

//ENTITY-COMPONENT
typedef std::bitset<MAX_COMPONENTS> SIGNATURE;	//A collections of bits to represent active components in an entity

enum COMPONENTID								//ID for each component, to be used to organise systems and map an entity
{
	ID_NullComponent = 0,
	ID_TransformComponent = 1,
	ID_SpriteComponent = 2
};					

enum SYSCATEGORY {
	SYS_NULL = 0,
	SYS_AI = 1,
	SYS_GRAPHICS,
	SYS_PHYSICS
};

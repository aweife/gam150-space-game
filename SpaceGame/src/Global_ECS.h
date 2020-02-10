#pragma once
#include <cstdint>
#include <bitset>

typedef uint32_t ENTITYID;					//ID for each entity, to be tagged to components
const ENTITYID ENTITY_MAX = 1000;			//Maximum number of entity in game
enum COMPONENTID							//ID for each component, to be used to organise systems and map an entity
{
	ID_NullComponent = 0,
	ID_TransformComponent = 1,
	ID_SpriteComponent = 2
};					



const uint16_t COMPONENT_MAX = 64;					//Maximum number of components that can be added to a entity
typedef std::bitset<COMPONENT_MAX> SIGNATURE;		//A collections of bits to represent active components 
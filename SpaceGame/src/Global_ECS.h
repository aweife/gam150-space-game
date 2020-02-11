#pragma once
#include <cstdint>
#include <bitset>


typedef unsigned int Entity; // ID for each entity, to be tagged to components
const Entity MAX_ENTITIES = 1000; // Maximum number of entity in game

typedef short ComponentType; // ID for component
const ComponentType MAX_COMPONENTS = 32; // Maximum number of components that can be added to a entity
typedef std::bitset<MAX_COMPONENTS> Signature; //A collections of bits to represent active components 

enum COMPONENTID							//ID for each component, to be used to organise systems and map an entity
{
	ID_NullComponent = 0,
	ID_TransformComponent = 1,
	ID_SpriteComponent = 2
};					

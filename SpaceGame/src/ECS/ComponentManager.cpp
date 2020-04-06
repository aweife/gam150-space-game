/*********************************************************************************
* \file			ComponentManager.cpp
* \brief		Manager for components and component storages in the game
* \author		Jun Yi, Chong, 50% Code Contribution
*        		Wei Feng, Ang, 50% Code Contribution
*
*				Responsible for adding components to their component storages
*				and provides a pointer to the component storage
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "ComponentManager.h"					// Self Header
#include <typeinfo>								// typeid
#include "../Components/ComponentList.h"
#include "../Tools/Console.h"

void ComponentManager::Init()
{
	//Register all the components here
	RegisterComponentCollection<cTransform>(ID_TransformComponent);
	RegisterComponentCollection<cSprite>(ID_SpriteComponent);
	RegisterComponentCollection<cRigidBody>(ID_RigidBodyComponent);
	RegisterComponentCollection<cCollision>(ID_CollisionComponent);
	RegisterComponentCollection<cCamera>(ID_CameraComponent);
	RegisterComponentCollection<cAI>(ID_AIComponent);
	RegisterComponentCollection<cBoss>(ID_BossComponent);
	RegisterComponentCollection<cSpaceShip>(ID_SpaceShip);
	RegisterComponentCollection<cUIElement>(ID_UIComponent);
	RegisterComponentCollection<cRangeWeapon>(ID_RangeWeaponComponent);
	RegisterComponentCollection<cMeleeWeapon>(ID_MeleeWeaponComponent);
	RegisterComponentCollection<cHealth>(ID_HealthComponent);
	RegisterComponentCollection<cProjectile>(ID_ProjectileComponent);
	RegisterComponentCollection<cDebugTools>(ID_DebugToolsComponent);
	RegisterComponentCollection<cParticle>(ID_ParticleComponent);
	RegisterComponentCollection<cParticleEmitter>(ID_ParticleEmitterComponent);
	RegisterComponentCollection<cTimeline>(ID_TimelineComponent);
	RegisterComponentCollection<cWarping>(ID_WarpingComponent);
	RegisterComponentCollection<cScanner>(ID_ScannerComponent);
}

template<typename T>
void ComponentManager::RegisterComponentCollection(ComponentType id)
{
	const char* componentTypeName = typeid(T).name();
	//Component already registered and in storage 
	if (componentCollection.find(componentTypeName) != componentCollection.end()) return;	

	//Create a new storage of components for that specific component type
	//To be shared by all relevant systems
	componentCollection.insert({componentTypeName, std::make_shared<ComponentStorage<T>>()});

	//Create relevant mapping from typename to enum
	componentClassToEnum.insert({componentTypeName, id });
}

//void ComponentManager::AddOrRemoveEntitySignature(ComponentType id, int set, ENTITY entity)
//{
//	SIGNATURE s = EntityManager.GetEntitySignature(entity);
//	s.set(id, set);
//	EntityManager.SetEntitySignature(entity, s);
//}


void ComponentManager::GenerateComponentCollection() const
{
	Console_Cout("---Generating Component Collection List---");
	for (auto& element : componentCollection)
	{
		Console_Cout(element.first/*, (int) &element.second*/);
	}
	Console_Newline();
}

void ComponentManager::EntityDestroyed(ENTITY entity)
{
	{
		// Check within each component storage if there was component for destroyed entity
		for (auto const& pair : componentCollection)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}
}


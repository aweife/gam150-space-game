#include "SystemManager.h"
#include "../Systems/SystemList.h"

void SystemManager::Init()
{
	// Register systems
	
	// Logic 
	RegisterSystem<SpaceShipLogicSystem>();
	RegisterSystem<PhysicsSystem>();
	RegisterSystem<CollisionSystem>();
	RegisterSystem<PathFindingSystem>();
	RegisterSystem<AISystem>();
	RegisterSystem<ParticleEmitterSystem>();

	// Rendering
	RegisterSystem<RenderSystem>();
	RegisterSystem<ParticleSystem>();
	RegisterSystem<UISystem>();
	RegisterSystem<DebugToolsSystem>();

	for (auto const& system : _systemMap)
	{
		system->Init();
	}
}

void SystemManager::Update()
{
	for (auto const& system : _systemMap)
	{
		system->Update();
	}
}

void SystemManager::Render()
{
	for (auto const& system : _systemMap)
	{
		system->Render();
	}
}

void SystemManager::EntityDestroyed(ENTITY entity)
{
	// Erase an entity from all system lists
	for (auto const& system : _systemMap)
	{
		if (system->entitiesList.find(entity) != system->entitiesList.end())
		{
			// The first of the pair is the system name
			// The second of the pair is the shared pointer to the system
			system->OnComponentRemove(entity);				//Remove the entity from the system tracking (Sprite Layers)
			system->entitiesList.erase(entity);
		}

	}
}

void SystemManager::UpdateEntitySignature(ENTITY entity, SIGNATURE entitySignature, SIGNATURE oldentitySignature)
{
	for (auto const& system : _systemMap)
	{
		// The first of the pair is the system name
		// The second of the pair is the shared pointer to the system
		const char* systemName = typeid(*system).name();
		auto const& systemSignature = _signaturesMap[systemName];

		// Do bitwise comparison of the signatures
		// The & operator returns a result for us to compare against
		// 01001101 & 00001100 = 00001100
		// 01000101 & 00001100 = 00000100 (Wrong entity)
		if ((entitySignature & systemSignature) == systemSignature)
		{
			// Entity signature matches system signature, add into set
			system->entitiesList.insert(entity);
			system->OnComponentAdd(entity);
		}
		else if((oldentitySignature & systemSignature) == systemSignature)
		{
			// Entity signature does not match system signature, erase from set
			// Will run erase on all systems 
			system->OnComponentRemove(entity);
			system->entitiesList.erase(entity);
		}
	}
}

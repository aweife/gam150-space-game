/*********************************************************************************
* \file			SystemManager.h
* \brief		Manager for all systems in the game
* \author		Chong Jun Yi, 50% Code Contribution
* \author		Ang Wei Feng, 50% Code Contribution
*
*				Register all systems and set their signatures. 
*				The system manager is also responsible for updating the systems.
*				
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include <memory>						//Shared Pointer
#include <algorithm>					//std::find for std::vector
#include <vector>						//systemMap should have a sorting order based on standard game flow
#include <unordered_map>				//systemSignature  
#include "AEEngine.h"					//AE Asserts
#include "../Global_ECS.h"				//ECS alias and typedef
#include "../Systems/System.h"

class SystemManager
{
public:
	void Init();
	// Shared pointers use reference counting - it is active as long as there
	// is at least one referencing it
	// We can create a pointer to the registered system and return it to core.

	void Update();
	void Render();

	// Returns a shared pointer to this system
	template<typename T>
	void RegisterSystem()
	{
		// Get name of the system
		const char* systemName = typeid(T).name();

		// Assert if the system already exists
		AE_ASSERT(std::find(_systemMapNames.begin(), _systemMapNames.end(), systemName) == _systemMapNames.end() 
			&&"Registering system more than once.");

		// Use make_share<T>() to make a shared pointer to the system
		// Using auto because we do not know the type
		std::shared_ptr<T> system = std::make_shared<T>();

		// Insert into system map as a pair: key value -- mapped value
		_systemMap.push_back(system);
		_systemMapNames.push_back(systemName);

		// Return the shared pointer
		//return system;
	}

	// Sets the unique signature for this system
	// The template is needed to get the name of the system
	template<typename T>
	void SetSignature(SIGNATURE signature)
	{
		// Get name of the system
		const char* systemName = typeid(T).name();

		// Assert if the system is used before registering it
		AE_ASSERT(std::find(_systemMapNames.begin(), _systemMapNames.end(), systemName) != _systemMapNames.end()
			&& "Using system before registering.");

		// Insert into signature map as a pair: key value -- mapped value
		_signaturesMap.insert({ systemName, signature });
	}

	// Erase an entity from all systems' entitiesList
	void EntityDestroyed(ENTITY entity);

	// Notify all systems an entity changed signature (add/remove component)
	void UpdateEntitySignature(ENTITY entity, SIGNATURE entitySignature, SIGNATURE oldentitySignature);

	template<typename T>
	std::shared_ptr<System> GetSystemInstance()
	{
		const char* systemName = typeid(T).name();

		AE_ASSERT(std::find(_systemMapNames.begin(), _systemMapNames.end(), systemName) != _systemMapNames.end()
			&& "Cannot find specifed system");

		auto it = std::find(_systemMapNames.begin(), _systemMapNames.end(), systemName);
		size_t index = it - _systemMapNames.begin();
		return _systemMap.at(index);
	}

private:
	// Map stores elements in pairs: A key value and a mapped value
	// The key value (.first) can be used to uniquely identify the mapped 
	// value (.second)
	// We use unordered map because it uses a hash table, which is O(1) speed

	// Map from string to a signature
	std::unordered_map<const char*, SIGNATURE> _signaturesMap;

	// Map from string to a system pointer
	std::vector<std::shared_ptr<System>> _systemMap;
	std::vector<const char*> _systemMapNames;
};
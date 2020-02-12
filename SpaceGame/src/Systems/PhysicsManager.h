#pragma once

#include "System.h"
#include "ComponentManager.h"
#include "../Components/ComponentStorage.h"
#include "../Components/SpriteComponent.h"

class PhysicsManager : public System<PhysicsManager>
{
private:

	// List of component
	std::shared_ptr<ComponentStorage<SpriteComponent>> spriteComponentList;
protected:

public:
	// constructor
	PhysicsManager();					//somehow cannot be accessed by system if placed anywhere else

	// Manager methods
	virtual void Init();								// Signature, assign componentStorages
	virtual void Update();								// Update physics on screen ect

};

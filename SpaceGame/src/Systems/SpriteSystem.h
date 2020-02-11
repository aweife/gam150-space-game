#pragma once
#include "System.h"
#include "ComponentManager.h"
#include "../Components/ComponentStorage.h"
#include "../Components/SpriteComponent.h"

class SpriteManager: public System<SpriteManager>
{
private:
	
	// List of component
	std::shared_ptr<ComponentStorage<SpriteComponent>> spriteComponentList;
protected:
	
public:
	// constructor
	SpriteManager();					//somehow cannot be accessed by system if placed anywhere else

	// Manager methods
	virtual void Init();								//Signature, assign componentStorages
	virtual void Update();								//Draw sprite on screen ect

};


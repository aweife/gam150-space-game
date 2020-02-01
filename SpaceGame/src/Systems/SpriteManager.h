#pragma once

#include <vector>
#include "../Components/SpriteComponent.h"

class SpriteManager
{
private:

	// Private constructor
	SpriteManager();

	// List of component
	std::vector<SpriteComponent> spriteComponentList;

public:

	// Manager methods
	void RegisterComponent(SpriteComponent& sprite);
	void UpdateComponents();
};


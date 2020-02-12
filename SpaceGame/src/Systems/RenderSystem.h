#pragma once
#include "System.h"

class RenderSystem : public System
{
private:
	//std::shared_ptr<ComponentStorage<SpriteComponent>> spriteComponentList
public:
	void Init();

	void Update() override;
};
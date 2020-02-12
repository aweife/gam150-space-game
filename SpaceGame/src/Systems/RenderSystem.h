#pragma once
#include "System.h"

class RenderSystem : public System
{
private:
	//std::shared_ptr<ComponentStorage<SpriteComponent>> spriteComponentList
public:
	void Init() override;

	void Update() override;

	void Render() override;
};
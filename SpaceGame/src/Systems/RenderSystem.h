#pragma once

#include "System.h"

class RenderSystem : public System
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
};
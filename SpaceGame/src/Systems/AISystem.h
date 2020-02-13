#pragma once

#include "System.h"

class AISystem : public System
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
};
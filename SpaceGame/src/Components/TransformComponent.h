#pragma once

#include "../Global.h"
#include "../Components/Component.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	float rotation;
	Vector2D scale;

	TransformComponent(ENTITYID parent);
};
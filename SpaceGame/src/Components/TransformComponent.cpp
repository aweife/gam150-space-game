#include "TransformComponent.h"

TransformComponent::TransformComponent(ENTITYID parent)
	: position{ 0.0f,0.0f }, rotation{ 0.0f }, scale{ 1.0f,1.0f }
{
	//Common Component variables
	_name = "class SpriteComponent";				//Do not change this otherwise remove component wont work
	_category = SYS_GRAPHICS;
	_componentID = ID_SpriteComponent;
	_entityParent = parent;
}

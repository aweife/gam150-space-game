#include "TransformManager.h"

void TransformManager::Reset(TransformComponent trans)
{
	trans.position = { 0.0f,0.0f };
	trans.rotation = 0.0f;
	trans.scale = { 1.0f,1.0f };
}
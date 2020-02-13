#include "cTransform.h"

cTransform::cTransform() : _position{ 0.0f, 0.0f }, _rotation{ 0.0f }, _scale{ 100.0f, 100.0f } {}

cTransform::cTransform(AEVec2 _position, float _rotation, AEVec2 _scale) 
	: _position{ _position }, _rotation{ _rotation }, _scale{ _scale } {}
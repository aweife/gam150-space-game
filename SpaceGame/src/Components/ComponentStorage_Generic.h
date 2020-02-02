#pragma once

class ComponentStorage_Generic
{
public:
	virtual ~ComponentStorage_Generic() = default;
	virtual void EntityDestroyed(ENTITYID entity) = 0;
};
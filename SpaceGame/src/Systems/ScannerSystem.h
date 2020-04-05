#pragma once

#include "System.h"					//Inheritance

class ScannerSystem : public System
{
public:
	ScannerSystem() = default;					//Virtual Constructor...
	~ScannerSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

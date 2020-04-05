#pragma once

#include "System.h"					//Inheritance

class ScannerSystem : public System
{
public:
	unsigned int planetScan;
	unsigned int hostileScan;
	unsigned int bossScan;
	unsigned int allyScan;
	std::set<ENTITY> markedForDestruction;					//Cant delete entity while looping with range loop
	std::set<ENTITY> markedForRemoveComp;

	ScannerSystem() = default;					//Virtual Constructor...
	~ScannerSystem() = default;					//...and destructor

	void Init() override;
	void Update() override;
	void Render() override {};
	void OnComponentAdd(ENTITY) override {};
	void OnComponentRemove(ENTITY) override {};
};

void ResetQuota(unsigned int planet, unsigned int hostile, unsigned int boss, unsigned int ally);
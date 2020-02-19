#pragma once
#include "System.h"

class UISystem :public System
{

public:
	UISystem() = default;
	~UISystem() = default;
	void Init() override;
	void Update() override {};
	void Render() override;
	void OnComponentAdd(ENTITY) {};
	void OnComponentRemove(ENTITY) {};

	void EditText(ENTITY target, const char* newText);
};
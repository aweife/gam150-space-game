#pragma once
#include "System.h"
#include "../Events/UIEvents.h"
#include "AEVec2.h"

enum class UI_ANCHOR
{
	CENTER,
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT
};

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

AEVec2 ScreenBasedCoords(float x, float y, UI_ANCHOR anchor, bool percentage = false);

bool OnHealthChange_HPUI(ENTITY entity, Events::OnHealthChange* message);
bool OnButtonClick_MainMenuUI(ENTITY entity, Events::OnMouseClick* message);
#pragma once
#include "System.h"
#include "../Events/UIEvents.h"
#include "AEVec2.h"
#include <set>

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
	std::set<ENTITY> choose3_Set;
	std::set<ENTITY> aiIndicator_Set;
	std::set<ENTITY> collectIndicator_Set;
	std::set<ENTITY> gameOver_Set;
	std::set<ENTITY> shieldBubble_Set;
	std::set<ENTITY> floatingDamage_Set;

	UISystem() = default;
	~UISystem() = default;
	void Init() override;
	void Update() override;
	void Render() override;
	void OnComponentAdd(ENTITY);
	void OnComponentRemove(ENTITY);

	void Check_AIIndicatorExist(ENTITY ai, AEVec2 aiDir, int aiType);
	void DeleteUpgradeWindow();
};
void EditText(ENTITY target, const char* newText);
void EditText(ENTITY target, const char* newText, int atBack);
AEVec2 ScreenBasedCoords(float x, float y, UI_ANCHOR anchor, bool percentage = false);

bool OnHealthChange_HPUI(ENTITY entity, Events::OnHealthChange* message);
bool OnLowHealth_HPIndicator(ENTITY entity, Events::OnLowHealth* message);
bool OnBossIncoming_EnemyIndicator(ENTITY entity, Events::OnBossIncoming* message);
bool OnShieldDown_ShieldIndicator(ENTITY entity, Events::OnShieldDown* message);
bool OnShieldChange_ShieldUI(ENTITY entity, Events::OnShieldChange* message);
bool OnShieldActivate_ShieldBubble(ENTITY entity, Events::OnShieldActivate* message);
bool OnThrusterChange_ThrusterUI(ENTITY entity, Events::OnThrusterChange* message);
bool OnButtonClick_MainMenuUI(ENTITY entity, Events::OnMouseClick* message);
bool OnButtonClick_Upgrades(ENTITY entity, Events::OnMouseClick* message);
bool OnButtonHover_Upgrades(ENTITY entity, Events::OnMouseHover* message);
bool TogglePauseWindow(ENTITY entity, Events::TogglePause* message);
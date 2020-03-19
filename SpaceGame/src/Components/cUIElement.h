#pragma once
#include "Component.h"
#include "../Global_Graphics.h"

enum class UI_TYPE
{
	NONE,
	TEXT,
	BUTTON,
	IMAGE,
};

enum class UI_ROLE
{
	NONE,
	HEALTH,
	SHIELD,
	SHIELDBUBBLE,
	THRUSTER,
	C3_FRAME,
	C3_FAKEUPGRADE,
	C3_UPGRADE,
	C3_TEXT,
	INDICATE_AI,
	INDICATE_COLLECT,
	GAMEOVER,
	BEGIN_BTN,
	CREDITS_BTN,
	OPTIONS_BTN,
	QUIT_BTN, 
	LOW_HEALTH_UI,
	SHIELD_DOWN_UI,
};

class cUIElement :public Component
{
public:
	//Data
	UI_TYPE _type = UI_TYPE::NONE;
	UI_ROLE _role = UI_ROLE::NONE;
	unsigned int _roleIndex = 0;

	//Text
	TextInfo _text;

	bool _isHovered;
	bool _isClicked;
	bool _isSelectable;
	bool _isActive = true;
	void (*_updateFP)(void);

	// Constructor with parameter
	cUIElement() = delete;
	cUIElement(UI_TYPE type, UI_ROLE role, unsigned int roleIndex = 0);
	cUIElement(const char* text, ColorInfo tint = {1,1,1,1}, ColorInfo blend = {1,1,1,1}, TEXT_ANCHOR anchor = TEXT_ANCHOR::CENTERLEFT);
	~cUIElement();										// Virtual Destructor

};
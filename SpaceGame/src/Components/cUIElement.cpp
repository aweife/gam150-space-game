/**********************************************************************************
* \file			cUIElement.cpp
* \brief		Paticle Emitter
* \author		Jun Yi,				Chong,  50% Code Contribution
*				Farzaana Binte,		Roslan,	50% Code Contribution
*
*				Handles data of UI Element
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "cUIElement.h"

cUIElement::cUIElement(UI_TYPE type, UI_ROLE role, unsigned int roleIndex)
	: _text{ {0} }, _type{ type }, _role{ role }, _roleIndex{ roleIndex }, _isHovered{ false }, _isClicked{ false },
	_isSelectable{ false }, _updateFP{ nullptr }
{

}

cUIElement::cUIElement(const char* text, ColorInfo tint, ColorInfo blend, TEXT_ANCHOR anchor)
	: _type{ UI_TYPE::TEXT }, _isHovered{ false }, _isClicked{ false }, _isSelectable{ false }, _updateFP{nullptr}
{
	sprintf_s(_text._textBuffer, text);
	_text._colorTint = tint;
	_text._colorBlend = blend;
	_text._anchor = anchor;
	_text._bufferCount = strlen(text);
	_text._usingScreenSpace = false;
}

cUIElement::~cUIElement()
{

}
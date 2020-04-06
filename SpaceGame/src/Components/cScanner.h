/**********************************************************************************
* \file			cScanner.h
* \brief		Scanner
* \author		Jun Yi,		Chong,  100% Code Contribution
*
*				Handles the scanner component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"
#include "../Global_Graphics.h"
enum class ScannerType
{
	NONE,
	PLANET,
	ENEMY,
	BOSS,
	ALLY,
	RECIEVER
};

class cScanner :public Component
{
public:
	TextInfo _textToDisplay;
	ScannerType _classification = ScannerType::NONE;
	float _displayTime = 0.0f;			//Only for recievers
	float _currTime = 0.0f;			//Only for recievers

	cScanner() = default;
	cScanner(const char* text, ScannerType type, ColorInfo tint = { 1,1,1,1 }, ColorInfo blend = { 1,1,1,1 }, TEXT_ANCHOR anchor = TEXT_ANCHOR::CENTERLEFT);
	void SetRecieverTime(float displayTime);
	~cScanner() = default;
};

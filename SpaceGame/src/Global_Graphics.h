/**********************************************************************************
* \file			Global_Graphics.h
* \brief		Custom structs for graphics concepts 
* \author		Jun Yi,			Chong,		100% Code Contribution
*				
*				Long Description
*				- RGBA color
*				- Text Alignment
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

struct ColorInfo
{
	float r;
	float g;
	float b;
	float a;
};

enum class SPRITE_RM
{
	RM_NONE,
	RM_COLOR,
	RM_SPRITE,
	RM_LINE
};

enum class TEXT_ANCHOR
{
	CENTER,
	CENTERLEFT,
	CENTERRIGHT
};


struct TextInfo
{
	char _textBuffer[200];
	size_t _bufferCount;
	ColorInfo _colorTint;
	ColorInfo _colorBlend;
	TEXT_ANCHOR _anchor = TEXT_ANCHOR::CENTERLEFT;
	bool _usingScreenSpace;
};



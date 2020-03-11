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
};



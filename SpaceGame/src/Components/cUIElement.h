#pragma once
#include "Component.h"

class cUIElement :public Component
{
public:
	//Data
	char _text[200];

	// Constructor with parameter
	cUIElement() = delete;
	cUIElement(const char* text);
	~cUIElement();										// Virtual Destructor

};
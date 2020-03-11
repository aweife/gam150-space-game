#pragma once
#include "Events.h"

namespace Events
{
	struct OnHealthChange :public EventsBase
	{
		OnHealthChange(float newHP) :_newHealth{ newHP }{};
		float _newHealth;
	};

	struct OnMouseClick :public EventsBase
	{
		OnMouseClick(float x, float y) :_xPos{ x }, _yPos{ y } {};
		float _xPos;
		float _yPos;
	};

	struct OnMouseHover :public EventsBase
	{
		OnMouseHover(float x, float y) :_xPos{ x }, _yPos{ y } {};
		float _xPos;
		float _yPos;
	};
}

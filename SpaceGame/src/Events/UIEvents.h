#pragma once
#include "Events.h"

namespace Events
{
	struct OnHealthChange :public EventsBase
	{
		OnHealthChange(float newHP) :_newHealth{ newHP }{};
		float _newHealth;
	};

	struct OnLowHealth :public EventsBase
	{
		OnLowHealth(){};
	};

	struct OnShieldChange :public EventsBase
	{
		OnShieldChange(float newShield) :_newShield{ newShield } {};
		float _newShield;
	};

	struct OnShieldActivate :public EventsBase
	{
		OnShieldActivate(){};
	};

	struct OnThrusterChange : public EventsBase
	{
		OnThrusterChange(float newVelocity, float capVelocity) : _newVelocity{ newVelocity }, _capVelocity{ capVelocity } {}
		float _newVelocity;
		float _capVelocity;
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

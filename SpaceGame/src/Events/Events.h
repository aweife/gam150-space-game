/*********************************************************************************
* \file			Events.h
* \brief		Manager for all events in the game
* \author		Jun Yi, Chong, 100% Code Contribution
*
*				Register all events and set their signatures.
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "../Global_ECS.h"

struct EventsBase
{
	
	bool _isResolved = false;
	bool _isRepeated = false;
};

struct EventsWrapperBase
{
	void Execute(EventsBase* event) { Call(event); }
	virtual void Call(EventsBase* event) = 0;
	virtual ENTITY GetEntity() const = 0;
	virtual bool GetStatus() const = 0;
};

template<class EventType>
struct EventsWrapper :public EventsWrapperBase
{
	bool (*_fp)(ENTITY, EventType*);
	ENTITY _entity;
	bool _lastStatus;

	EventsWrapper(ENTITY entity, bool (*fp)(ENTITY, EventType*)) :_fp{ fp }, _entity{ entity }, _lastStatus{false}{}

	void Call(EventsBase* event) override
	{
		//Downcasting
		_lastStatus = _fp(_entity, static_cast<EventType*>(event));
	}

	ENTITY GetEntity() const
	{
		return _entity;
	}

	bool GetStatus() const
	{
		return _lastStatus;
	}
};
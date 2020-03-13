/**********************************************************************************
* \file			UIEventsManager.h
* \brief		Stores all upgrade values for weapon
* \author		Jun Yi,		Chong,		100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include <unordered_map>
#include <list>
#include <typeindex>
#include "../Events/Events.h"
#include "../Events/UIEvents.h"

namespace UIEventsManager
{
	typedef std::list<EventsWrapperBase*> handlerList;
	extern std::unordered_map<std::type_index, handlerList*> subscribersMap;

	template<class EventMessage>
	bool Broadcast(EventMessage* message)
	{
		if (subscribersMap.size() <= 0)
		{
			delete message;
			return false;
		}
		handlerList* handlers = subscribersMap[typeid(EventMessage)];
		if (handlers == nullptr) 
		{
			delete message;
			return false;
		}
		bool result = false;

		for (typename handlerList::value_type& i : *handlers)
		{
			if (i != nullptr)
			{
				i->Execute(message);
				if (i->GetStatus())
				{
					result = true;
				}
			}
		}
		delete message;
		return result;
	}

	template<class EventMessage>
	void Subscribe(ENTITY entity, bool (*executeFP)(ENTITY, EventMessage*))
	{
		//Identify the type of event from message type id
		//inserts a new key if does not exist
		handlerList* handlers = subscribersMap[typeid(EventMessage)];

		if (handlers == nullptr)
		{
			handlers = new handlerList();
			subscribersMap[typeid(EventMessage)] = handlers;
		}

		//Add the subscriber's event function to subscribersMap
		handlers->push_back(new EventsWrapper<EventMessage>(entity, executeFP));
	}

	template<class EventMessage>
	void UnSubscribe(ENTITY entity)
	{
		handlerList* handlers = subscribersMap[typeid(EventMessage)];

		std::list<EventsWrapperBase*>::iterator iter = std::find_if(handlers->begin(), handlers->end()
			, [entity](EventsWrapperBase* i) {return i->GetEntity() == entity; });

		delete* iter;
		handlers->erase(iter);
	}

	void Cleanup();
};

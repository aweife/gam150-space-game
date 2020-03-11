#include "UIEventsManager.h"

namespace UIEventsManager
{
	std::unordered_map<std::type_index, handlerList*> subscribersMap;

	void Cleanup()
	{
		for (auto it = subscribersMap.begin(); it != subscribersMap.end(); ++it)
		{
			if (it->second != nullptr)
			{
				for (auto j = it->second->begin(); j != it->second->end(); ++j)
				{
					//Delete each wrapper inside the list
					if (*j != nullptr)
					{
						delete *j;
						*j = nullptr;
					}
				}
				it->second->clear();
				//Delete the list
				delete it->second;
				it->second = nullptr;
			}
		}
		subscribersMap.clear();
	}
}
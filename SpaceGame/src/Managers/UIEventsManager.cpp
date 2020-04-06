/**********************************************************************************
* \file			UIEventsManager.cpp
* \brief		Manages the UI for Events
* \author		Chong Jun Yi, 100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

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
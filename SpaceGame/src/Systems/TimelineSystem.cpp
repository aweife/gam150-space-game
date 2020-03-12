#include "TimelineSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"
#include "../Components/cTimeline.h"

void TimelineSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTimeline>());
	Core::Get().SetSystemSignature<TimelineSystem>(signature);
}

void TimelineSystem::Update()
{
	cTimeline* timelineComp;

	for (auto const& entity : entitiesList)
	{
		timelineComp = Core::Get().GetComponent<cTimeline>(entity);

		if (timelineComp->_currTime < timelineComp->_startTime)
		{
			continue;			//not time to start yet
		}
		for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
		{
			for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2)
			{
				if (it2->first > g_appTime) 
				{
					float timeDiff = it2->first - g_appTime;
					float valueDiff1 = 0.0f;
					int valueDiff2 = 0;
					switch (it2->second->_type)
					{
						case TimelineType::FLOAT:
							valueDiff1 = it2->second->_floatValue - *it->first->_floatRef;
							if (timeDiff > g_dt)
							{
								*it->first->_floatRef += valueDiff1 / timeDiff * g_dt;
							}
							else
							{
								*it->first->_floatRef += valueDiff1;
							}
							// Uncompleted...
							break;
						case TimelineType::INT:
							valueDiff2 = it2->second->_intValue - *it->first->_intRef;
							if (timeDiff > g_dt)
							{
								*it->first->_intRef += static_cast<int>(valueDiff2 / timeDiff * g_dt);
							}
							else
							{
								*it->first->_floatRef += valueDiff1;
							}
							break;
						case TimelineType::FUNCTION:
							if (timeDiff < g_dt)
							{
								(*it->first->_functionCall)(it2->second->_functionParam);
							}
							break;
					}
				}
			}
		}

		timelineComp->_currTime += g_dt;

		if (timelineComp->_currTime >= timelineComp->_endTime)
		{
			markedForRemoval.insert(entity);
			continue;
		}
	}

	if (markedForRemoval.size() > 0 )
	{
		for (auto const& entity : markedForRemoval)
		{
			Core::Get().RemoveComponent<cTimeline>(entity);
		}
		markedForRemoval.clear();
	}
}
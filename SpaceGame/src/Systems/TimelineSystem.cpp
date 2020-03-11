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

		timelineComp->_currTime += g_dt;

		for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
		{
			for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2)
			{
				if (it2->first < g_appTime) 
				{
					float timeDiff = g_appTime - it2->first;
					switch (it2->second->_type)
					{
						case TimelineType::FLOAT:
							*(it->first) 
							break;
						case TimelineType::INT:

							break;
					}
				}
			}
		}
	}
}
#include "cTimeline.h"

#include "../Tools/Console.h"

cTimeline::cTimeline(float startTime, float endTime)
	:_startTime{ startTime }, _currTime{ startTime }, _endTime{endTime}
{

}

cTimeline::~cTimeline()
{
	for (auto it = timelineTable.begin(); it != timelineTable.end(); ++it)
	{
		for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2)
		{
			delete it2->second;
			it2->second = nullptr;
		}
		delete it->second;
		it->second = nullptr;
		delete it->first;	
	}
	Console_Cout("Deleted cTimeline");
}

std::unordered_map<TimelineReference*, std::vector<std::pair<float, TimelineNode*>>*> timelineTable;
void AddNewTimeline_Float(float* reference, cTimeline* timelineComp)
{
	//Check if timeline already exist
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_floatRef == reference)
		{
			return;
		}
	}
	std::vector <std::pair<float, TimelineNode*>> * innerTimeline = new std::vector <std::pair<float, TimelineNode*>>;
	TimelineReference* timelineID = new TimelineReference;
	timelineID->_floatRef = reference;
	auto iterator = timelineComp->timelineTable.emplace(timelineID, innerTimeline);
}

void AddNewTimeline_Int(int* reference, cTimeline* timelineComp)
{
	//Check if timeline already exist
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_intRef == reference)
		{
			return;
		}
	}
	std::vector <std::pair<float, TimelineNode*>>* innerTimeline = new std::vector <std::pair<float, TimelineNode*>>;
	TimelineReference* timelineID = new TimelineReference;
	timelineID->_intRef = reference;
	auto iterator = timelineComp->timelineTable.emplace(new TimelineReference, innerTimeline);
}

//NO SORTING AS OF YET...
void AddNewNode_Int(int* reference, cTimeline* timelineComp, float time, int value)
{
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_intRef == reference)
		{
			TimelineNode* node = new TimelineNode;
			node->_intValue = value;
			node->_type = TimelineType::INT;
			it->second->push_back({ timelineComp->_currTime + time, node });
		}
	}
}

void AddNewNode_Float(float* reference, cTimeline* timelineComp, float time, float value)
{
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_floatRef == reference)
		{
			TimelineNode* node = new TimelineNode;
			node->_floatValue = value;
			node->_type = TimelineType::FLOAT;
			it->second->push_back({ timelineComp->_currTime + time, node });
		}
	}
}
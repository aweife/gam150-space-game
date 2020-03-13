#include "cTimeline.h"
#include "../Global.h"
#include "../Tools/Console.h"

cTimeline::cTimeline(float startTime, float endTime, bool looping)
	:_startTime{ startTime }, _currTime{ g_appTime }, _endTime{endTime}, _isLooping{ looping }
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
	auto iterator = timelineComp->timelineTable.emplace(timelineID, innerTimeline);
}

void AddNewTimeline_Void(void(*reference)(ENTITY), cTimeline* timelineComp)
{
	//Check if timeline already exist
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_functionCall == reference)
		{
			return;
		}
	}
	std::vector <std::pair<float, TimelineNode*>>* innerTimeline = new std::vector <std::pair<float, TimelineNode*>>;
	TimelineReference* timelineID = new TimelineReference;
	timelineID->_functionCall = reference;
	auto iterator = timelineComp->timelineTable.emplace(timelineID, innerTimeline);
}

void AddNewTimeline_Bool(bool* reference, cTimeline* timelineComp)
{
	//Check if timeline already exist
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_boolRef == reference)
		{
			return;
		}
	}
	std::vector <std::pair<float, TimelineNode*>>* innerTimeline = new std::vector <std::pair<float, TimelineNode*>>;
	TimelineReference* timelineID = new TimelineReference;
	timelineID->_boolRef = reference;
	auto iterator = timelineComp->timelineTable.emplace(timelineID, innerTimeline);
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
			it->second->push_back({ timelineComp->_startTime + time, node });
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
			it->second->push_back({ timelineComp->_startTime + time, node });
		}
	}
}

void AddNewNode_Void(void(*reference)(ENTITY), cTimeline* timelineComp, float time, ENTITY param1)
{
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_functionCall == reference)
		{
			TimelineNode* node = new TimelineNode;
			node->_functionCall = reference;
			node->_functionParam = param1;
			node->_type = TimelineType::FUNCTION;
			it->second->push_back({ timelineComp->_startTime + time, node });
		}
	}
}

void AddNewNode_Bool(bool* reference, cTimeline* timelineComp, float time, bool value)
{
	for (auto it = timelineComp->timelineTable.begin(); it != timelineComp->timelineTable.end(); ++it)
	{
		if (it->first->_boolRef == reference)
		{
			TimelineNode* node = new TimelineNode;
			node->_boolValue = value;
			node->_type = TimelineType::BOOL;
			it->second->push_back({ timelineComp->_startTime + time, node });
		}
	}
}
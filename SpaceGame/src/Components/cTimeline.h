#pragma once

#include "AEEngine.h"
#include "Component.h"
#include <vector>
#include <unordered_map>

enum class TimelineType
{
	FLOAT, INT, FUNCTION
};

struct TimelineNode
{
	TimelineType _type;
	float _floatValue;
	int _intValue;
	void(*_functionCall)(ENTITY);
	ENTITY _functionParam;
};

union TimelineReference
{
	float* _floatRef;
	int* _intRef;
	void(*_functionCall)(ENTITY);
};

class cTimeline :public Component
{
public:
	float _startTime;
	float _currTime;
	float _endTime;
	std::unordered_map<TimelineReference*, std::vector<std::pair<float, TimelineNode*>>*> timelineTable;


	cTimeline() = delete;
	cTimeline(float startTime, float endTime);
	~cTimeline();
};

void AddNewTimeline_Float(float* reference, cTimeline* timelineComp);
void AddNewTimeline_Int(int* reference, cTimeline* timelineComp);
void AddNewTimeline_Void(void(*reference)(ENTITY), cTimeline* timelineComp);

void AddNewNode_Int(int* reference, cTimeline* timelineComp, float time, int value);
void AddNewNode_Float(float* reference, cTimeline* timelineComp, float time, float value);
void AddNewNode_Void(void(*reference)(ENTITY), cTimeline* timelineComp, float time, ENTITY param1);

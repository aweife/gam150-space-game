#pragma once

#include "AEEngine.h"
#include "Component.h"
#include <vector>
#include <unordered_map>

enum class TimelineType
{
	FLOAT, INT
};

struct TimelineNode
{
	TimelineType _type;
	float _floatValue;
	int _intValue;
};

union TimelineReference
{
	float* _floatRef;
	int* _intRef;
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
void AddNewNode_Int(int* reference, cTimeline* timelineComp, float time, int value);
void AddNewNode_Float(float* reference, cTimeline* timelineComp, float time, float value);

/**********************************************************************************
* \file			cTimeline.h
* \brief		Timeline
* \author		Jun Yi,		Chong,  100% Code Contribution
*
*				Handles the timeline component
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "AEEngine.h"
#include "Component.h"
#include <vector>
#include <unordered_map>

enum class TimelineType
{
	FLOAT, INT, FUNCTION, BOOL
};

struct TimelineNode
{
	TimelineType _type;
	float _floatValue;
	int _intValue;
	void(*_functionCall)(ENTITY);
	ENTITY _functionParam;
	bool _boolValue;
};

union TimelineReference
{
	float* _floatRef;
	int* _intRef;
	bool* _boolRef;
	void(*_functionCall)(ENTITY);
};

class cTimeline :public Component
{
public:
	float _startTime;
	float _currTime;
	float _endTime;
	bool _isLooping;
	std::unordered_map<TimelineReference*, std::vector<std::pair<float, TimelineNode*>>*> timelineTable;


	cTimeline() = delete;
	cTimeline(float startTime, float endTime, bool looping);
	~cTimeline();
};

void AddNewTimeline_Float(float* reference, cTimeline* timelineComp);
void AddNewTimeline_Int(int* reference, cTimeline* timelineComp);
void AddNewTimeline_Void(void(*reference)(ENTITY), cTimeline* timelineComp);
void AddNewTimeline_Bool(bool *reference, cTimeline* timelineComp);

void AddNewNode_Int(int* reference, cTimeline* timelineComp, float time, int value);
void AddNewNode_Float(float* reference, cTimeline* timelineComp, float time, float value);
void AddNewNode_Void(void(*reference)(ENTITY), cTimeline* timelineComp, float time, ENTITY param1);
void AddNewNode_Bool(bool* reference, cTimeline* timelineComp, float time, bool value);
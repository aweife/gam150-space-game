#pragma once
#include <Windows.h>

//------------------------------------
// Gameplay Global Variables

extern bool gGamePause;
extern double gStartTime;
extern float g_dt;

void Global_Init();
void TogglePause();

struct Vector2D
{
	float x;
	float y;
};
#pragma once

//------------------------------------
// Gameplay Global Variables
extern bool gGamePause;
extern double gStartTime;
extern float g_dt;
extern float g_appTime;

void Global_Init();
void TogglePause();

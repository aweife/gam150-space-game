#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

namespace Global 
{
	extern bool gGamePause;
	extern double gStartTime;

	void Global_Init();
	void TogglePause();
}


#endif

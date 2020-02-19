//Include This header in individual cpp files to check which linke is causing MemLeak

//#include "../Tools/MemoryLeak.h"

#pragma once
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

////////////////////////////////////////////////////////////////////////
// Take Note ... dont use cos it will detect static as memory leak
// _CrtDumpMemoryLeaks();
////////////////////////////////////////////////////////////////////////
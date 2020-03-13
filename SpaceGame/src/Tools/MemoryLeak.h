/**********************************************************************************
* \file			MemoryLeak.h
* \brief		Include this in individual cpp files to check which line is causing MemLeak
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
//#include "../Tools/MemoryLeak.h"

#pragma once
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

////////////////////////////////////////////////////////////////////////
// Take Note ... dont use cos it will detect static as memory leak
// _CrtDumpMemoryLeaks();
////////////////////////////////////////////////////////////////////////
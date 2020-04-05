/**********************************************************************************
* \file			Editor.h
* \brief		Low level editor using console to modify game variables
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

void Editor_Init();

void Editor_Update();

void Editor_Render();

void Editor_TrackVariable(const char* text, float value);

void Editor_TrackVariable(const char* text, int value);

void Editor_SetSize(short x, short y);
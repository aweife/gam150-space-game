/**********************************************************************************
* \file			Math.h
* \brief		Abstraction of math functions
* \author		Jun Yi,			Chong,		50% Code Contribution
*				Farzaana Binte, Roslan,		50% Code Contribution
*
*				Long Description
*				- Smooth increment (lerp, step)
*				- Vector2D maths
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

struct AEVec2;

float MBMath_Lerp(float a, float b, float time);

float MBMath_LerpRotation(float a, float b, float time);

float MBMath_Smoothstep(float edge0, float edge1, float x);

float MBMath_Clamp(float x, float lowerlimit, float upperlimit);

float MBMath_SmoothDamp(float current, float target, float* currentVelocity, float smoothTime, float baseMaxSpeed, float deltaTime);

float MBMath_DotProduct(const AEVec2& a, const AEVec2& b);

// For Vectors
float MBMath_getLengthofVector(const AEVec2& vector);

AEVec2 MBMath_getNormalizedVector(const AEVec2& vector);

AEVec2 MBMath_getNormalofVector(const AEVec2& vector);

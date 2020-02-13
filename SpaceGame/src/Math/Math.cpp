#include "Math.h"
#include <cmath>
#include "AEEngine.h"
float MBMath_Lerp(float a, float b, float time)
{
	return a + ((b - a) * time);
}

float MBMath_Smoothstep(float edge0, float edge1, float x) 
{
    // Scale, bias and saturate x to 0..1 range
    x = MBMath_Clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    // Evaluate polynomial
    return x * x * (3 - (2 * x)); //(3-2x)x^2
}

// Keep x within lowerLimit and upperLimit...if exceed will set x to the min and max
float MBMath_Clamp(float x, float lowerlimit, float upperlimit) 
{
    if (x < lowerlimit)
        x = lowerlimit;
    if (x > upperlimit)
        x = upperlimit;
    return x;
}

float MBMath_SmoothDamp(float current, float target, float* currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
    smoothTime = AEMax(0.0001f, smoothTime);                                        //smoothTime cant be too small
    float num = 2.0f / smoothTime;                                                  //         
    float num2 = num * deltaTime;                                                   //
    float num3 = 1.0f /                                                             //
        (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);          //
    float num4 = current - target;                                                  //
    float num5 = target;                                                            //
    float num6 = maxSpeed * smoothTime;                                             //
    num4 = AEClamp(num4, -num6, num6);                                              //
    target = current - num4;                                                        //
    float num7 = (*currentVelocity + num * num4) * deltaTime;                        //
    *currentVelocity = (*currentVelocity - num * num7) * num3;                        //
    float num8 = target + (num4 + num7) * num3;                                     //
    if (num5 - current > 0.0f == num8 > num5)                                       //
    {
        num8 = num5;
        *currentVelocity = (num8 - num5) / deltaTime;
    }
    return num8;
}
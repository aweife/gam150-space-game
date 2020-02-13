#include "cCamera.h"

cCamera::cCamera(cTransform* target, float followSpeed): _followTarget {target}
{
	_name = "cCamera";
	_followSpeed = followSpeed;
}

void cCamera::Init()
{

}
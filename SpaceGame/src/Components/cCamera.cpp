#include "cCamera.h"

cCamera::cCamera(cTransform* target, float followSpeed, bool dynamic) : _followTarget{ target }, _isdynamic{dynamic}
{
	_name = "cCamera";
	_followSpeed = followSpeed;
}

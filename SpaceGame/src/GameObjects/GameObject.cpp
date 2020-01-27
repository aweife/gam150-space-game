#include "GameObject.h"
#include <string>

GameObject::GameObject(const std::string& name, unsigned short heirachy)
	:_name{ name }, _heirachy{ heirachy }
{
	component_bitflag = 0;
}
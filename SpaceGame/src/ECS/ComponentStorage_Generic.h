/*********************************************************************************
* \file			ComponentStorage_Generic.h
* \brief		Abstract class for a generic component storage
* \author		Jun Yi, Chong, 50% Code Contribution
*				
*				Component Storage
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

class ComponentStorage_Generic							//Abstract class
{
public:
	virtual ~ComponentStorage_Generic() = default;		//Derived destructor for Component Storage
	virtual void EntityDestroyed(ENTITY entity) = 0;	//Pure virtual function	
};
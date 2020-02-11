/*********************************************************************************
* \file			MemoryPool.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			31/01/2019
* \par			Memory Management
* \note			Course: GAM150
* \brief		Intend to use to control new and delete, however will not be used
				- Preallocate a fixed memory block for game to use

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
//#include "MemoryPool.h"
//#include "AEEngine.h"
//#include "../Tools/Console.h"		//Remove later
//
//#include <iostream>
//
//
//
// Null, because instance will be initialized on demand. 
//MemoryPool* MemoryPool::instance = 0;

/******************************************************************************/
/*!
  \brief	Get singleton instance
*/
/******************************************************************************/
//MemoryPool& MemoryPool::GetInstance()
//{
//	if (!instance)
//	{
//		instance = new MemoryPool();
//	}
//
//	AE_ASSERT(instance);	//Assert if fail to create 
//	return *instance;
//}

/******************************************************************************/
/*!
  \brief	Destroy singleton instance
*/
/******************************************************************************/
//void MemoryPool::DestroyInstance()
//{
//	delete instance;
//}

/******************************************************************************/
/*!
  \brief	Constructor for memory pool, together with preallocated chunk on stack
*/
/******************************************************************************/
//MemoryPool::MemoryPool()// : stackPtr{mem}
//{
//	Need this for singleton instance
//	memset(mem, 0, memPoolCapacity);
//	stackPtr = mem;
//}
//
/******************************************************************************/
/*!
  \brief	Assign a dyanamic allocated memory onto the memory pool location
*/
/******************************************************************************/
//void* MemoryPool::Allocate(int memSize)
//{
//	AE_ASSERT(stackPtr + memSize <= mem + sizeof(mem));		//Check if new allocate will exceed memory pool
//
//	void* memoryLocation = stackPtr;
//	std::cout << "Alloc Mem Location " << std::hex << memoryLocation << '\n';
//	stackPtr += memSize;
//	return memoryLocation;
//}

/******************************************************************************/
/*!
  \brief	Remove the memory from memory pool
*/
/******************************************************************************/
//void MemoryPool::Deallocate(int memSize, void* memAdd)
//{
//	UNREFERENCED_PARAMETER(memSize);
//	UNREFERENCED_PARAMETER(memAdd);
//	memset(memAdd, 0, memSize); //This is bad
//	Defragment
//}
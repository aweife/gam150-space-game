#include "MemoryPool.h"
#include "AEEngine.h"
#include "..//Tools/Console.h"		//Remove later

// Null, because instance will be initialized on demand. 
MemoryPool* MemoryPool::instance = 0;

MemoryPool& MemoryPool::GetInstance()
{
	if (!instance)
	{
		instance = new MemoryPool();
	}

	AE_ASSERT(instance);	//Assert if fail to create 
	return *instance;
}

void MemoryPool::DestroyInstance()
{
	delete instance;
}

MemoryPool::MemoryPool()// : stackPtr{mem}
{
	//Need this for singleton instance
	memset(mem, 0, memPoolCapacity);
	stackPtr = mem;
}

//TESTING ... deleted later
void  MemoryPool::GetMem()
{
	Console_Cout("mem", (int)(mem));
	Console_Cout("stackptr", (int)(stackPtr));
}

void* MemoryPool::Allocate(int memSize)
{
	AE_ASSERT(stackPtr + memSize <= mem + sizeof(mem));		//Check if new allocate will exceed memory pool

	void* memoryLocation = stackPtr;
	stackPtr += memSize;
	return memoryLocation;
}

void MemoryPool::Deallocate(int memSize, void* memAdd)
{
	memset(memAdd, 0, memSize);
	//Defragment
}
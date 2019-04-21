#ifndef BUDDYALLOCATOR_MEMORYBLOCK_H
#define BUDDYALLOCATOR_MEMORYBLOCK_H
#define MIN_POWER 5

#include "BlockStatus.h"

class MemoryBlock
{
public:
    MemoryBlock(short level, MemoryBlock* next);
    ~MemoryBlock();

    BlockStatus status;
    short level;
    MemoryBlock* previous = nullptr;
    MemoryBlock* next;
    MemoryBlock* buddy = nullptr;

    void* allocatedMemoryPtr;
};

#endif //BUDDYALLOCATOR_MEMORYBLOCK_H

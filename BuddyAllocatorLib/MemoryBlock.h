#ifndef BUDDYALLOCATOR_MEMORYBLOCK_H
#define BUDDYALLOCATOR_MEMORYBLOCK_H
#define MIN_POWER 5

#include "BlockStatus.h"

class MemoryBlock
{
public:
    MemoryBlock(short level, MemoryBlock* previous, MemoryBlock* next);
    ~MemoryBlock();

    BlockStatus status;
    short level;
    MemoryBlock* previous;
    MemoryBlock* next;

    void* allocatedMemoryPtr;

    void splitOnBuddies(MemoryBlock& firstBuddy, MemoryBlock& secondBuddy);
    MemoryBlock* unionWith(MemoryBlock* buddyBlock);
};

#endif //BUDDYALLOCATOR_MEMORYBLOCK_H

#ifndef BUDDYALLOCATOR_ALLOCATOR_H
#define BUDDYALLOCATOR_ALLOCATOR_H

#include "MemoryBlock.h"
#include <cstddef>

class Allocator
{
public:
    ~Allocator();

    explicit Allocator(size_t pullSize);
    void* Allocate(size_t size);
    void Free(void* blockPointer);

    void Dump();

private:
    size_t pullSize;
    short levelsCount;
    MemoryBlock** blocksList;
    int* countOfFreeBlocksOnLevel;

    static short getNecessaryLevel(size_t memorySize);
    MemoryBlock* findFreeBlockOnCustomLevel(short level);
    MemoryBlock* splitOnBuddies(MemoryBlock* memoryBlock);
    MemoryBlock* combineWithBuddy(MemoryBlock* memoryBlock);
};

#endif //BUDDYALLOCATOR_ALLOCATOR_H

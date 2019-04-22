#ifndef BUDDYALLOCATOR_ALLOCATOR_H
#define BUDDYALLOCATOR_ALLOCATOR_H
#define MIN_POWER 5

#include "BorderDescriptor.h"
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
    void* memoryPool;
    short levelsCount;
    BorderDescriptor** descriptorsList;
    short* countOfDescriptorsOnLevel;
    short* countOfFreeBlocksOnLevel;

    static short getNecessaryLevel(size_t memorySize);
    static size_t getBlockSize(short level);
    BorderDescriptor* findFreeBlockOnCustomLevel(short level);
    BorderDescriptor* splitOnBuddies(BorderDescriptor* splitDescriptor);
    BorderDescriptor* combineWithBuddy(BorderDescriptor* memoryBlock);
};

#endif //BUDDYALLOCATOR_ALLOCATOR_H

#include "MemoryBlock.h"
#include <iostream>
#include <cmath>

MemoryBlock::MemoryBlock(const short level, MemoryBlock* previous, MemoryBlock* next)
{
    this->level = level;
    this->previous = previous;
    this->next = next;
    status = BlockStatus::Free;

    auto dataSize = (size_t)pow(2, level + MIN_POWER);
    allocatedMemoryPtr = malloc(dataSize);
}

MemoryBlock::~MemoryBlock()
{
    free(allocatedMemoryPtr);
}

void MemoryBlock::splitOnBuddies(MemoryBlock& firstBuddy, MemoryBlock& secondBuddy)
{

}

MemoryBlock* MemoryBlock::unionWith(MemoryBlock* buddyBlock)
{
    return nullptr;
}

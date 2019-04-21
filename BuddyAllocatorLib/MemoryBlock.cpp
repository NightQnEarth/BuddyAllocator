#include "MemoryBlock.h"
#include <iostream>
#include <cmath>

MemoryBlock::MemoryBlock(const short level, MemoryBlock* next)
{
    this->level = level;
    this->next = next;
    status = BlockStatus::Free;

    auto dataSize = (size_t)pow(2, level + MIN_POWER);
    allocatedMemoryPtr = malloc(dataSize);
}

MemoryBlock::~MemoryBlock()
{
    free(allocatedMemoryPtr);
}

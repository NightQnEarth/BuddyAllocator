#include "Allocator.h"
#include "BlockStatus.h"
#include <cmath>
#include <iostream>
#include <intrin.h>

Allocator::Allocator(size_t pullSize)
{
    this->pullSize = pullSize;
    levelsCount = getNecessaryLevel(pullSize);
    freeBlocksLists = new MemoryBlock*[levelsCount];
    freeBlocksLists[levelsCount - 1] = new MemoryBlock(levelsCount, nullptr, nullptr);
    mask = 0x1 << (levelsCount - 1);
    std::cout << _bit_scan_reverse(mask) << std::endl;
}

Allocator::~Allocator()
{
    delete[](freeBlocksLists);
}

void* Allocator::Allocate(size_t size)
{
    return nullptr;
}

void Allocator::Free(void* blockPointer)
{

}

void Allocator::Dump()
{

}

short Allocator::getNecessaryLevel(size_t memorySize)
{
    return std::fmax(ceil(log2(memorySize)) - MIN_POWER + 1, 0);
}

MemoryBlock* Allocator::findSuitableFreeBlocksList(short level)
{
    return nullptr;
}

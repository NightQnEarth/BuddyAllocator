#include "Allocator.h"
#include "BlockStatus.h"
#include <cmath>
#include <iostream>
#include <intrin.h>

Allocator::Allocator(size_t pullSize)
{
    this->pullSize = pullSize;
    levelsCount = getNecessaryLevel(pullSize);
    blocksList = new MemoryBlock*[levelsCount];
    blocksList[levelsCount - 1] = new MemoryBlock(levelsCount, nullptr); // TODO: Delete malloc from MemoryBlock. Just one allocation.
    countOfFreeBlocksOnLevel = new int[levelsCount];
    countOfFreeBlocksOnLevel[levelsCount - 1] = 1;

    for (int i = 0; i < levelsCount - 1; ++i)
    {
        blocksList[i] = nullptr;
        countOfFreeBlocksOnLevel[i] = 0;
    }
}

Allocator::~Allocator()
{
    delete[](blocksList);
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

MemoryBlock* Allocator::findFreeBlockOnCustomLevel(short level)
{
    while (level <= levelsCount && countOfFreeBlocksOnLevel[level] == 0) level++;

    if (level > levelsCount) std::__throw_out_of_range("Out of allocator memory resource.");

    MemoryBlock* foundBlock = blocksList[level];

    while (foundBlock->status != BlockStatus::Free)
        foundBlock = foundBlock->next;

    return foundBlock;
}

MemoryBlock* Allocator::splitOnBuddies(MemoryBlock* memoryBlock)
{
    short newLevel = memoryBlock->level - 1;
    auto secondBuddy = new MemoryBlock(newLevel, blocksList[newLevel]);
    auto firstBuddy = new MemoryBlock(newLevel, secondBuddy);
    secondBuddy->buddy = firstBuddy;
    firstBuddy->buddy = secondBuddy;

    if (blocksList[memoryBlock->level] == memoryBlock)
        blocksList[memoryBlock->level] = memoryBlock->next;

    if (memoryBlock->previous)
        memoryBlock->previous->next = memoryBlock->next;
    if (memoryBlock->next)
        memoryBlock->next->previous = memoryBlock->previous;

    if (memoryBlock->buddy)
        memoryBlock->buddy->buddy = nullptr;

    countOfFreeBlocksOnLevel[memoryBlock->level]--;

    delete(memoryBlock);

    return firstBuddy;
}

MemoryBlock* Allocator::combineWithBuddy(MemoryBlock* memoryBlock)
{
    short newLevel = memoryBlock->level + 1;
    auto unionBlock = new MemoryBlock(newLevel, blocksList[newLevel]);
    unionBlock->buddy = blocksList[newLevel];

    if (unionBlock->buddy)
        unionBlock->buddy->previous = unionBlock;


}

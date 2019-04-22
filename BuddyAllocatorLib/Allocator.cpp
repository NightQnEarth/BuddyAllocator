#include "Allocator.h"
#include "BlockStatus.h"
#include <cmath>
#include <iostream>
#include <intrin.h>

Allocator::Allocator(size_t pullSize)
{
    this->pullSize = pullSize;
    levelsCount = getNecessaryLevel(pullSize);

    descriptorsList = new BorderDescriptor*[levelsCount];
    countOfDescriptorsOnLevel = new short[levelsCount];
    countOfFreeBlocksOnLevel = new short[levelsCount];

    memoryPool = malloc((size_t)pow(2, levelsCount));

    descriptorsList[levelsCount - 1] = new BorderDescriptor(memoryPool, levelsCount, 0);
    countOfDescriptorsOnLevel[levelsCount - 1] = 1;
    countOfFreeBlocksOnLevel[levelsCount - 1] = 1;

    for (short i = 0; i < levelsCount - 1; ++i)
    {
        descriptorsList[i] = nullptr;
        countOfFreeBlocksOnLevel[i] = 0;
        countOfDescriptorsOnLevel[i] = 0;
    }
}

Allocator::~Allocator()
{
    free(memoryPool);
    delete[](descriptorsList);
    delete[](countOfDescriptorsOnLevel);
    delete[](countOfFreeBlocksOnLevel);
}

void* Allocator::Allocate(size_t size)
{
    short levelOfDesiredBlock = getNecessaryLevel(size);
    BorderDescriptor* desiredDescriptor = findFreeBlockForCustomLevel(levelOfDesiredBlock);
    while (desiredDescriptor->level > fmax(levelOfDesiredBlock, 0))
        desiredDescriptor = splitOnBuddies(desiredDescriptor);

    desiredDescriptor->status = BlockStatus::Reserved;
    return desiredDescriptor->memoryBlock;
}

void Allocator::Free(void* blockPointer)
{
    BorderDescriptor* exemptedBlock = (BorderDescriptor*)blockPointer - 1;
    exemptedBlock->status = BlockStatus::Free;

    while (findAccessibleBuddyDescriptor(exemptedBlock) != nullptr)
        exemptedBlock = tryToCombineWithBuddy(exemptedBlock);
}

void Allocator::Dump()
{

}

short Allocator::getNecessaryLevel(size_t memorySize)
{
    return std::fmax(ceil(log2(memorySize)) - MIN_POWER + 1, 0);
}

size_t Allocator::getBlockSize(short level)
{
    return pow(2, level + MIN_POWER);
}

BorderDescriptor* Allocator::findFreeBlockForCustomLevel(short level)
{
    while (level <= levelsCount && countOfFreeBlocksOnLevel[level] == 0) level++;

    if (level > levelsCount) std::__throw_out_of_range("Out of allocator memory resource.");

    BorderDescriptor* foundDescriptor = descriptorsList[level];
    while (foundDescriptor->status != BlockStatus::Free)
        foundDescriptor = foundDescriptor->next;

    return foundDescriptor;
}

BorderDescriptor* Allocator::splitOnBuddies(BorderDescriptor* splitDescriptor)
{
    short newLevel = splitDescriptor->level - 1;
    short firstBuddyIndex = splitDescriptor->indexOnLevel * 2;

    BorderDescriptor* firstBuddy;
    BorderDescriptor* secondBuddy;

    if (countOfDescriptorsOnLevel[newLevel] < firstBuddyIndex)
    {
        firstBuddy = new BorderDescriptor(splitDescriptor->memoryBlock, newLevel, firstBuddyIndex);
        auto pointerOnSecondHalfOfMemoryBlock = (void*)((size_t)splitDescriptor->memoryBlock + getBlockSize(newLevel));
        secondBuddy = new BorderDescriptor(pointerOnSecondHalfOfMemoryBlock, newLevel, firstBuddyIndex + 1);

        firstBuddy->next = secondBuddy;
        secondBuddy->previous = firstBuddy;

        BorderDescriptor* lastDescriptorOnLevel = descriptorsList[newLevel];
        while (lastDescriptorOnLevel != nullptr && lastDescriptorOnLevel->next != nullptr)
            lastDescriptorOnLevel = lastDescriptorOnLevel->next;

        firstBuddy->previous = lastDescriptorOnLevel;
        if (lastDescriptorOnLevel != nullptr)
            lastDescriptorOnLevel->next = firstBuddy;

        countOfDescriptorsOnLevel[newLevel] += 2;
    }
    else
    {
        firstBuddy = descriptorsList[newLevel];
        while (firstBuddy->indexOnLevel != firstBuddyIndex)
            firstBuddy = firstBuddy->next;
        secondBuddy = firstBuddy->next;

        firstBuddy->status = BlockStatus::Free;
        secondBuddy->status = BlockStatus::Free;
    }

    countOfFreeBlocksOnLevel[newLevel] += 2;

    splitDescriptor->status = BlockStatus::Split;
    countOfFreeBlocksOnLevel[splitDescriptor->level]--;

    return firstBuddy;
}

BorderDescriptor* Allocator::findAccessibleBuddyDescriptor(BorderDescriptor* descriptor)
{
    BorderDescriptor* buddyDescriptor = descriptor->indexOnLevel % 2 == 0 ? descriptor->next : descriptor->previous;

    if (buddyDescriptor == nullptr || buddyDescriptor->status != BlockStatus::Free) return nullptr;
}

BorderDescriptor* Allocator::tryToCombineWithBuddy(BorderDescriptor* descriptor)
{
    BorderDescriptor* buddyDescriptor = findAccessibleBuddyDescriptor(descriptor);

    if (descriptor->status != BlockStatus::Free || buddyDescriptor == nullptr)
        return nullptr;

    short parentBlockLevel = descriptor->level + 1;
    BorderDescriptor* parentDescriptor = descriptorsList[parentBlockLevel];
    while (parentDescriptor->indexOnLevel != descriptor->indexOnLevel / 2)
        parentDescriptor = parentDescriptor->next;

    descriptor->status = BlockStatus::Unallocated;
    buddyDescriptor->status = BlockStatus::Unallocated;
    parentDescriptor->status = BlockStatus::Free;

    return parentDescriptor;
}

#include "BorderDescriptor.h"

BorderDescriptor::BorderDescriptor(void* memoryBlock, short level, int indexOnLevel) :
        memoryBlock(memoryBlock),
        level(level),
        indexOnLevel(indexOnLevel),
        status(BlockStatus::Free) { }

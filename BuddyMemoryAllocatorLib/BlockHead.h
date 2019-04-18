#ifndef BUDDYMEMORYALLOCATOR_BLOCKHEAD_H
#define BUDDYMEMORYALLOCATOR_BLOCKHEAD_H

#include "BlockStatus.h"

struct BlockHead
{
    BlockStatus status;
    short level;
    BlockHead* previous;
    BlockHead* next;
};

#endif //BUDDYMEMORYALLOCATOR_BLOCKHEAD_H

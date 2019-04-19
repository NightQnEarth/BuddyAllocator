#ifndef BUDDYALLOCATOR_BLOCKHEAD_H
#define BUDDYALLOCATOR_BLOCKHEAD_H

#include "BlockStatus.h"

struct BlockHead
{
    BlockStatus status;
    short level;
    BlockHead* previous;
    BlockHead* next;
};

#endif //BUDDYALLOCATOR_BLOCKHEAD_H
